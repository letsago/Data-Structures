from flask import Flask

app = Flask(__name__)
# pylint: disable=maybe-no-member
app.jinja_env.add_extension('pyjade.ext.jinja.PyJadeExtension')
app.config.from_envvar('SERVER_SETTINGS')

# because app is needed for the files below, we must import these files after we define app 
from server.database import db_session
import server.views

@app.teardown_appcontext
def shutdown_session(exception=None):
    db_session.remove()
