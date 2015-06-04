import sys
import os
from twisted.internet import reactor

from twisted.web import server, resource
from twisted.web.static import File
from twisted.python import log
from datetime import datetime
from renderHtml import RenderHtml
from renderHtml import PointFile 

import time


if __name__ == '__main__':
    cheminLocal = os.getcwd()
    portServeurWeb = 8080

    root = File(cheminLocal) 
    server = server.Site(root)
    
    root.putChild('', RenderHtml())
    root.putChild('points', PointFile())
    
    log.startLogging(sys.stdout)
    log.msg('Starting server: %s' %str(datetime.now()))

    
    # Serveur Web
    reactor.listenTCP(portServeurWeb, server) #@UndefinedVariable
    reactor.run() #@UndefinedVariable
