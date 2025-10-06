import sys

#!/usr/bin/env python3


print("Content-Type: text/html")
print()  # End of headers

# Intentional errors below
print("<html>")
print("<head><title>Broken CGI</title></head>")
print("<body>")

# Syntax error
if True
	print("<p>This line has a syntax error!</p>")

# Name error
print(undefined_variable)

print("</body>")
print("</html>")