import random
import string
import cherrypy

class webGUI(object):
    @cherrypy.expose
    def index(self):
     return """<html>
          <head></head>
          <body>

            <form method="get" action="SetPosition">
              <input type="text" value="0" name="altitude" />
              <button type="submit">Set Altitude</button><br>

	      <input type="text" value="0" name="azimuth" />
              <button type="submit">Set Azimuth</button>
            </form>

          </body>
        </html>"""

    @cherrypy.expose
    def SetPosition(self, altitude, azimuth):
        #Here you paste your code of your Serial read write
        return

if __name__ == '__main__':
    cherrypy.quickstart(webGUI())
