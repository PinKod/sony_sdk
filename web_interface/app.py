from flask import Flask, render_template, request, jsonify
import os
import time

app = Flask(__name__)

# Configuration
FILE_PAIRS = {
    'focus_mode': ('../build/focus_mode.list', '../build/focus_mode.nfo', '../build/focus_mode.set'),
    'shoot_mode': ('../build/shoot_mode.list', '../build/shoot_mode.nfo', '../build/shoot_mode.set'),
    'apperture': ('../build/aperture.list', '../build/aperture.nfo', '../build/aperture.set'),
    'shutter': ('../build/shutter_speed.list', '../build/shutter_speed.nfo', '../build/shutter_speed.set'),
    'iso': ('../build/iso.list', '../build/iso.nfo', '../build/iso.set'),
    'exposure_bias_compensation': ('../build/exposure_bias_compensation.list', '../build/exposure_bias_compensation.nfo', '../build/exposure_bias_compensation.set'),
    'white_balance': ('../build/white_balance.list', '../build/white_balance.nfo', '../build/white_balance.set'),
    'jpeg_quality': ('../build/jpeg_quality.list', '../build/jpeg_quality.nfo', '../build/jpeg_quality.set'),
    'remain_photos': (None, '../build/remain_photos.nfo', None),  # Read-only setting
    'live_veiw_quality': ('../build/live_veiw_quality.list', '../build/live_veiw_quality.nfo', '../build/live_veiw_quality.set'),
    'zoom_scale': (None, '../build/zoom_scale.nfo', None),  # Read-only setting
}


def read_file(filename):
    if not filename:
        return []
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
        # Handle form submission for writable settings
        if set_file and request.method == 'POST' and f'set_{setting_name}' in request.form:
            new_value = request.form[f'{setting_name}_select']
            with open(set_file, 'w') as f:
                f.write(new_value + '\n')
        
        # Get current values
        options = read_file(list_file)
        current_value = get_current_setting(nfo_file)
        settings_data[setting_name] = {
            'options': options,
            'current': current_value,
            'writable': set_file is not None  # Flag for template
        }

    return render_template('index.html', settings=settings_data)

@app.route('/get_remain_photos')
def get_remain_photos():
    return jsonify({
        'value': get_current_setting(FILE_PAIRS['remain_photos'][1])
    })

@app.route('/get_zoom_scale')
def get_zoom_scales():
    return jsonify({
        'value': get_current_setting(FILE_PAIRS['zoom_scale'][1])
    })

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, threaded=True)