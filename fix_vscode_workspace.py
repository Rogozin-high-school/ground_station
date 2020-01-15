import os
import json
import subprocess

if not os.path.exists(".vscode"):
    os.makedirs(".vscode")

data = {
    "C_Cpp.default.includePath": [
        "include"
    ],
    "C_Cpp.default.defines": [
        "LOGGING",
        "LOGGING_FUNCTION_CALLS"
    ],
    "files.exclude": {
        "ground_station": True,
        ".vscode": True,
        ".gitignore": True,
        "res": False,
        "*.py": False,
        "*.md": False
    },
    "editor.minimap.enabled": False
}

output = subprocess.run(["pkg-config","--cflags", "gtkmm-3.0"], stdout = subprocess.PIPE, universal_newlines = True).stdout
gtk_include_path = ("/" + s for s in output.split(" -I/")[1:])
data["C_Cpp.default.includePath"].extend(gtk_include_path)

with open(".vscode/settings.json", "w") as write_file:
    json.dump(data, write_file, indent=4)
