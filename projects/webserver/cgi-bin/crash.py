import sys

#!/usr/bin/env python3

raise Exception("Intentional crash for CGI testing")

# Output required CGI header
print("Content-Type: text/html")
print()  # End of headers

# Intentional errors below
print("<html>")
print("<head><title>Broken CGI</title></head>")
print("<body>")

# Deliberately crash the script