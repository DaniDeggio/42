#!/usr/bin/env python3

import os
import sys
from urllib.parse import parse_qs

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
UPLOADS_DIR = os.path.normpath(os.path.join(BASE_DIR, "../www/main/uploads"))


def get_files_in_uploads():
    """Ottiene la lista dei file validi nella cartella uploads"""
    if not os.path.isdir(UPLOADS_DIR):
        return []

    try:
        return [
            item
            for item in sorted(os.listdir(UPLOADS_DIR))
            if os.path.isfile(os.path.join(UPLOADS_DIR, item))
        ]
    except OSError:
        return []

def handle_get_request():
    """Gestisce le richieste GET - ritorna l'HTML con i file nella select"""
    files = get_files_in_uploads()
    
    # Se non ci sono file, mostra un messaggio
    if not files:
        options_html = '<option value="">No files available</option>'
    else:
        options_html = ""
        for file in files:
            options_html += f'<option value="{file}">{file}</option>\n'
    
    html_content = f'''<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Delete Resource</title>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&display=swap');

        .container{{
            --max-width: 1000px;
            --padding: 1rem;

            width: min(var(--max-width), 100% - (var(--padding) * 1.2));
            margin-inline: auto;
        }}
        body {{
            margin: 0;
            height: 100vh;
            font-family: 'Inter', sans-serif;
            background: linear-gradient(135deg, #ffffff, #f3824d);
            display: flex;
            justify-content: center;
            align-items: center;
            color: #333;
            text-align: center;
            padding: 1rem;
            overflow: hidden;
        }}
        div {{
            font-size: 1.5rem;
            font-weight: semibold;
            color: #333;
            text-align: center;
        }}
        .button{{
            border: none;
            padding: 1rem 3rem;
            background-color: #333;
            border-radius: 15px;
            font-weight: semibold;
            color: #f0f0f0;
            cursor: pointer;
        }}
        .refresh-btn{{
            background-color: #007bff;
            margin-left: 1rem;
        }}
        select {{
            padding: 0.5rem;
            font-size: 1rem;
            border-radius: 5px;
            border: 1px solid #ccc;
            margin: 1rem;
        }}
    </style>
</head>
<body>
    <div class="container">
        <h2>Delete a Resource</h2>
        <form id="deleteForm">
            <label for="resource">Select a resource to delete:</label>
            <select id="resource" name="resource">
                {options_html}
            </select>
            <br><br>
            <button type="button" class="button" onclick="deleteResource()">Delete</button>
        </form>
        <p id="responseMessage"></p>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/js-confetti@latest/dist/js-confetti.browser.js"></script>

<script>
    const jsConfetti = new JSConfetti()
    
    function deleteResource() {{
        const resource = document.getElementById('resource').value;
        
        if (!resource) {{
            document.getElementById('responseMessage').innerText = 'Please select a file to delete.';
            jsConfetti.addConfetti({{
                emojis: ['⚠️'],
            }})
            return;
        }}
        
        fetch('/cgi-bin/delete.py', {{
            method: 'POST',
            headers: {{
                'Content-Type': 'application/x-www-form-urlencoded',
            }},
            body: 'resource=' + encodeURIComponent(resource),
        }})
        .then(response => response.text())
        .then(data => {{
            // si le mot error è nella risposta, mostra errore
            if (data.includes('error') || data.includes('not exist') || data.includes('Error')) {{
                document.getElementById('responseMessage').innerText = data;
                jsConfetti.addConfetti({{
                    emojis: ['❌'],
                }})
                return;
            }}

            jsConfetti.addConfetti({{
                confettiColors: ['#ff00ff', '#00ffff'],
                confettiRadius: 8,
            }})
            document.getElementById('responseMessage').innerText = data;
            
            // Rimuovi l'opzione cancellata dal menu
            const select = document.getElementById('resource');
            const optionToRemove = select.querySelector(`option[value="${{resource}}"]`);
            if (optionToRemove) {{
                optionToRemove.remove();
            }}
        }})
        .catch(error => {{
            document.getElementById('responseMessage').innerText = 'Error: ' + error.message;
            jsConfetti.addConfetti({{
                emojis: ['❌'],
            }})
        }});
    }}
</script>
</body>
</html>'''
    
    return html_content

def handle_delete_request():
    """Gestisce le richieste DELETE - cancella il file specificato"""
    # Ottieni il parametro resource dalla query string
    query_string = os.environ.get('QUERY_STRING', '')
    params = parse_qs(query_string)
    
    # Se il parametro non è nella query string, prova a leggerlo dal body (POST)
    if 'resource' not in params:
        try:
            content_length = int(os.environ.get('CONTENT_LENGTH', '0'))
        except ValueError:
            content_length = 0

        if content_length > 0:
            body = sys.stdin.read(content_length)
            body_params = parse_qs(body)
            for key, values in body_params.items():
                if key in params:
                    params[key].extend(values)
                else:
                    params[key] = values

    if 'resource' not in params:
        return "Error: No resource specified"
    
    resource = params['resource'][0]
    file_path = os.path.join(UPLOADS_DIR, resource)
    abs_file_path = os.path.abspath(file_path)

    # Validazione sicurezza: assicurati che il path sia nella cartella uploads
    if not abs_file_path.startswith(UPLOADS_DIR + os.sep):
        return "Error: Invalid file path"
    
    try:
        if os.path.exists(abs_file_path) and os.path.isfile(abs_file_path):
            os.remove(abs_file_path)
            return f"Successfully deleted {resource}"
        else:
            return f"Error: File {resource} does not exist"
    except Exception as e:
        return f"Error deleting file: {str(e)}"

def main():
    """Funzione principale che gestisce le richieste"""
    # Imposta le intestazioni HTTP
    print("Content-Type: text/html")
    print("Cache-Control: no-cache")
    print()
    
    # Determina il metodo HTTP
    request_method = os.environ.get('REQUEST_METHOD', 'GET')
    
    if request_method == 'GET':
        # Mostra la pagina con i file
        html_content = handle_get_request()
        print(html_content)
    elif request_method in ('DELETE', 'POST'):
        # Cancella il file specificato
        result = handle_delete_request()
        print(result)
    else:
        print("Error: Unsupported method")

if __name__ == "__main__":
    main()
