from server.database import db_session
from flask import Flask

app = Flask(__name__)
# pylint: disable=maybe-no-member
app.jinja_env.add_extension('pyjade.ext.jinja.PyJadeExtension')

import server.views

@app.teardown_appcontext
def shutdown_session(exception=None):
    db_session.remove()
