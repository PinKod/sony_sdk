from flask import Flask, render_template, request
import os
import glob

app = Flask(__name__)

# Configuration
FILE_PAIRS = {
    'focus_mode': ('./../build/focus_mode.list', './../build/focus_mode.nfo', './../build/focus_mode.set'),
    'shoot_mode': ('./../build/shoot_mode.list', './../build/shoot_mode.nfo', './../build/shoot_mode.set'),
    'iso': ('./../build/iso.list', './../build/iso.nfo', './../build/iso.set'),
    'shutter': ('./../build/shutter.list', './../build/shutter.nfo', './../build/shutter.set')
}

def read_file(filename):
    try:
        with open(filename, 'r') as f:
            return f.read().splitlines()
    except FileNotFoundError:
        return []

def get_current_setting(nfo_file):
    try:
        with open(nfo_file, 'r') as f:
            return f.read().strip()
    except FileNotFoundError:
        return 'Not available'

@app.route('/', methods=['GET', 'POST'])
def index():
    settings_data = {}
    
    for setting_name, (list_file, nfo_file, set_file) in FILE_PAIRS.items():
        # Handle form submission
        if request.method == 'POST' and f'set_{setting_name}' in request.form:
            new_value = request.form[f'{setting_name}_select']
            with open(set_file, 'w') as f:
                f.write(new_value + '\n')
        
        # Get current values
        options = read_file(list_file)
        current_value = get_current_setting(nfo_file)
        settings_data[setting_name] = {
            'options': options,
            'current': current_value,
            'set_file': set_file
        }

    return render_template('index.html', settings=settings_data)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)