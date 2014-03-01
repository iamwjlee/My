from django.shortcuts import render

from django.http import HttpResponse

# Create your views here.a


def main_page(request):
	output='''
		<html>
			<head><title>%s</title></head>
				<body>
					<h1>%s</h1> <p>%s</p>
				</body>
		</html>
	''' % ( 'title', 'head', 'body')

	return HttpResponse(output)				
