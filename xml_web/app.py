from flask import Flask, render_template, request, send_file, Response
import os

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
    'remain_photos': (None, '../build/remain_photos.nfo', None),
    'live_view_quality': ('../build/live_view_quality.list', '../build/live_view_quality.nfo', '../build/live_view_quality.set'),
    'zoom_scale': (None, '../build/zoom_scale.nfo', None),
}

CTRL_TO_SETTING = {
    'fm': 'focus_mode',
    'pm': 'shoot_mode',
    'iso': 'iso',
    'shutter': 'shutter',
    'aperture': 'apperture',
    'ev': 'exposure_bias_compensation',
    'wb': 'white_balance',
    'jq': 'jpeg_quality',
}

ACTION_COMMANDS = {
    'focus': '../build/focus.set',
    'take': '../build/take.set',
    'startvid': '../build/startvid.set',
    'stopvid': '../build/stopvid.set',
    'zoomminus': '../build/zoomminus.set',
    'zoomplus': '../build/zoomplus.set',
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
        return 'N/A'

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/cgi/xport')
def xport():
    act = request.args.get('act', '')
    
    if act == 'preview':
        return send_file('../build/cap.jpg', mimetype='image/jpeg')
    
    elif act == 'set':
        ctrl = request.args.get('ctrl', '')
        val = request.args.get('val', '')
        
        if ctrl in CTRL_TO_SETTING:
            setting = CTRL_TO_SETTING[ctrl]
            list_file, _, set_file = FILE_PAIRS[setting]
            
            if not set_file:
                return Response(status=403)
            
            options = read_file(list_file)
            try:
                selected = options[int(val)]
                with open(set_file, 'w') as f:
                    f.write(selected + '\n')
                return Response(status=200)
            except (IndexError, ValueError):
                return Response(status=400)
        
        elif ctrl in ACTION_COMMANDS:
            try:
                with open(ACTION_COMMANDS[ctrl], 'w') as f:
                    f.write('1\n')
                return Response(status=200)
            except FileNotFoundError:
                return Response(status=500)
        
        return Response(status=400)
    
    elif act == 'getstatus':
        status = {}
        # Add settings from CTRL_TO_SETTING
        for ctrl, setting in CTRL_TO_SETTING.items():
            _, nfo_file, _ = FILE_PAIRS[setting]
            status[f'o-{ctrl}'] = get_current_setting(nfo_file)
        
        # Add read-only settings
        status['o-remain_photos'] = get_current_setting(FILE_PAIRS['remain_photos'][1])
        status['o-zoom_scale'] = get_current_setting(FILE_PAIRS['zoom_scale'][1])
        
        xml = '<?xml version="1.0"?><data>'
        for key, value in status.items():
            xml += f'<{key}>{value}</{key}>'
        xml += '</data>'
        return Response(xml, mimetype='text/xml')
    
    elif act == 'getparams':
        params = {}
        for ctrl, setting in CTRL_TO_SETTING.items():
            list_file, _, _ = FILE_PAIRS[setting]
            params[f'o-{ctrl}_lst'] = ';'.join(read_file(list_file))
        
        xml = '<?xml version="1.0"?><data>'
        for key, value in params.items():
            xml += f'<{key}>{value}</{key}>'
        xml += '</data>'
        return Response(xml, mimetype='text/xml')
    
    return Response(status=400)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)