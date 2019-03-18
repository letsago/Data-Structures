from server import app
from flask_socketio import SocketIO, emit

socketio = SocketIO(app)
active_user_count = 0

def update_active_user_count(count_delta):
    global active_user_count
    active_user_count += count_delta
    emit('showActiveUserCount', active_user_count, broadcast=True)     

@socketio.on('connect') 
def connect():
    update_active_user_count(1)

@socketio.on('disconnect')
def disconnect():
    update_active_user_count(-1)

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=3001)
