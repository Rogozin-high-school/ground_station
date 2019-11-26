python3 << END
import os
import json
import subprocess

if not os.path.exists(".vscode"):
    os.makedirs(".vscode")

data = {
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "include"
            ]
        }
    ],
    "version": 4
}

output = subprocess.run(["pkg-config","--cflags", "gtkmm-3.0"], stdout = subprocess.PIPE, universal_newlines = True).stdout
gtk_include_path = ("/" + str for str in output.split(" -I/")[1:])
data["configurations"][0]["includePath"].extend(gtk_include_path)

with open(".vscode/c_cpp_properties.json", "w") as write_file:
    json.dump(data, write_file, indent=4)

data = {
    "files.exclude": {
        ".vscode": True,
        ".gitignore": True,
        "*.md": True,
        "bin": True,
        "res": True,
        "*.sh": True,
        "*.py": True
    }
}

with open(".vscode/settings.json", "w") as write_file:
    json.dump(data, write_file, indent=4)
END
