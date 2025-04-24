# import os
# import time
# from flask import Flask, render_template, request, Response, send_file

# app = Flask(__name__)

# # Configuration - Update this path to match your build directory
# SETTINGS_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build/'))

# ALLOWED_SETTINGS = [
#     'focus_mode', 'shoot_mode', 'iso', 'aperture', 'shutter_speed',
#     'exposure_bias_compensation', 'white_balance', 'jpeg_quality',
#     'live_veiw_quality'
# ]

# @app.route('/')
# def index():
#     return render_template('index.html')

# # @app.route('/get_current_settings')
# # def get_current_settings():
# #     settings = {}
# #     for setting in ALLOWED_SETTINGS:
# #         nfo_path = os.path.join(SETTINGS_DIR, f"{setting}.nfo")
# #         try:
# #             with open(nfo_path, 'r') as f:
# #                 settings[setting] = f.read().strip()
# #         except IOError:
# #             settings[setting] = 'N/A'
    
# #     xml = '<settings>\n'
# #     for name, value in settings.items():
# #         xml += f'  <setting name="{name}">{value}</setting>\n'
# #     xml += '</settings>'
# #     return Response(xml, mimetype='text/xml')

# @app.route('/get_current_settings')
# def get_current_settings():
#     settings = {}
#     for setting in ALLOWED_SETTINGS:
#         nfo_path = os.path.join(SETTINGS_DIR, f"{setting}.nfo")
#         settings[setting] = 'N/A'  # Default value
        
#         # Retry logic with short delay
#         retries = 3
#         while retries > 0:
#             try:
#                 with open(nfo_path, 'r') as f:
#                     content = f.read().strip()
#                     if content:
#                         settings[setting] = content
#                         break
#                 retries -= 1
#                 time.sleep(0.1)  # Short delay between retries
#             except (IOError, FileNotFoundError):
#                 retries -= 1
#                 time.sleep(0.1)
    
#     xml = '<settings>\n'
#     for name, value in settings.items():
#         xml += f'  <setting name="{name}">{value}</setting>\n'
#     xml += '</settings>'
#     return Response(xml, mimetype='text/xml')


# # @app.route('/get_options/<setting>')
# # def get_options(setting):
# #     if setting not in ALLOWED_SETTINGS:
# #         return Response('<options></options>', mimetype='text/xml')
    
# #     list_path = os.path.join(SETTINGS_DIR, f"{setting}.list")
# #     options = []
# #     try:
# #         with open(list_path, 'r') as f:
# #             options = [line.strip() for line in f if line.strip()]
# #     except IOError:
# #         pass
    
# #     xml = '<options>\n'
# #     for opt in options:
# #         xml += f'  <option>{opt}</option>\n'
# #     xml += '</options>'
# #     return Response(xml, mimetype='text/xml')

# @app.route('/get_options/<setting>')
# def get_options(setting):
#     if setting not in ALLOWED_SETTINGS:
#         return Response('<options></options>', mimetype='text/xml')
    
#     list_path = os.path.join(SETTINGS_DIR, f"{setting}.list")
#     options = []
#     try:
#         # Retry logic for empty files
#         retries = 5
#         while retries > 0:
#             with open(list_path, 'r') as f:
#                 options = [line.strip() for line in f if line.strip()]
#                 if options:  # Stop retrying if we got options
#                     break
#                 retries -= 1
#                 time.sleep(0.1)  # Short delay before retry
#     except IOError:
#         pass
    
#     # Add default option if empty
#     if not options:
#         options = ['Waiting for options...']
    
#     xml = '<options>\n'
#     for opt in options:
#         xml += f'  <option>{opt}</option>\n'
#     xml += '</options>'
#     return Response(xml, mimetype='text/xml')

# @app.route('/set_setting', methods=['POST'])
# def set_setting():
#     setting = request.form.get('setting')
#     value = request.form.get('value')
    
#     if setting not in ALLOWED_SETTINGS:
#         return 'Invalid setting', 400
    
#     set_path = os.path.join(SETTINGS_DIR, f"{setting}.set")
#     try:
#         with open(set_path, 'w') as f:
#             f.write(value)
#         return 'Success'
#     except IOError as e:
#         return f'Error: {str(e)}', 500

# @app.route('/capture')
# def capture():
#     image_path = os.path.join(SETTINGS_DIR, 'cap.jpg')
#     return send_file(image_path, mimetype='image/jpeg')

# if __name__ == '__main__':
#     app.run(host='0.0.0.0', port=5000, debug=True)













import os
import time
from flask import Flask, render_template, request, Response, send_file

app = Flask(__name__)
SETTINGS_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build/'))
ALLOWED_SETTINGS = [
    'focus_mode', 'shoot_mode', 'iso', 'aperture', 'shutter_speed',
    'exposure_bias_compensation', 'white_balance', 'jpeg_quality',
    'live_veiw_quality', 'focus_mode_settings'  # Add new setting
]

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/get_current_settings')
def get_current_settings():
    settings = {}
    for setting in ALLOWED_SETTINGS:
        nfo_path = os.path.join(SETTINGS_DIR, f"{setting}.nfo")
        settings[setting] = 'N/A'
        retries = 3
        while retries > 0:
            try:
                with open(nfo_path, 'r') as f:
                    content = f.read().strip()
                    if content:
                        settings[setting] = content
                        break
                time.sleep(0.1)
            except IOError:
                retries -= 1
            finally:
                retries -= 1
    xml = '<settings>\n'
    for name, value in settings.items():
        xml += f'  <setting name="{name}">{value}</setting>\n'
    xml += '</settings>'
    return Response(xml, mimetype='text/xml')

@app.route('/get_options/<setting>')
def get_options(setting):
    if setting not in ALLOWED_SETTINGS:
        return Response('<options></options>', mimetype='text/xml')
    
    list_path = os.path.join(SETTINGS_DIR, f"{setting}.list")
    options = []
    
    try:
        retries = 5
        while retries > 0:
            try:
                with open(list_path, 'r') as f:
                    options = [line.strip() for line in f if line.strip()]
                if options:
                    break
            except IOError:
                pass
            time.sleep(0.1)
            retries -= 1
            
        if not options:
            if setting == 'live_veiw_quality':
                options = ['Loading live view...']
            else:
                options = ['No options available']
    except Exception as e:
        return Response(f'<error>{str(e)}</error>', mimetype='text/xml', status=500)
        
    xml = '<options>\n'
    for opt in options:
        xml += f'  <option>{opt}</option>\n'
    xml += '</options>'
    return Response(xml, mimetype='text/xml')

@app.route('/set_setting', methods=['POST'])
def set_setting():
    setting = request.form.get('setting')
    value = request.form.get('value')
    
    if setting not in ALLOWED_SETTINGS:
        return 'Invalid setting', 400
        
    set_path = os.path.join(SETTINGS_DIR, f"{setting}.set")
    try:
        with open(set_path, 'w') as f:
            f.write(value)
        return 'Success'
    except IOError as e:
        return f'Error: {str(e)}', 500

@app.route('/capture')
def capture():
    image_path = os.path.join(SETTINGS_DIR, 'cap.jpg')
    return send_file(image_path, mimetype='image/jpeg')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)