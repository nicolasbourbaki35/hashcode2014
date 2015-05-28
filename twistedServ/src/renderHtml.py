from twisted.web import resource
import netifaces as ni

class RenderHtml(resource.Resource):
    
    def __init__(self):
        resource.Resource.__init__(self)
       
    def render_GET(self, request):
       indexFile = open('../html/index.html')
       return indexFile.read()

    def render_POST(self, request):
        return self.render_GET(request)

