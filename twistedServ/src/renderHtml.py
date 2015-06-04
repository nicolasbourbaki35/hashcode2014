from twisted.web import resource

class RenderHtml(resource.Resource):
    
    def __init__(self):
        resource.Resource.__init__(self)
       
    def render_GET(self, request):
       indexFile = open('../html/index.html')
       return indexFile.read()

    def render_POST(self, request):
        return self.render_GET(request)

class PointFile(resource.Resource):
    def __init__(self):
        resource.Resource.__init__(self)
       
    def render_GET(self, request):
       file = open('../resources/' + request.args["file"][0])
       return file.read()

