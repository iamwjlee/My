from django.shortcuts import render
from django.http import HttpResponse
from django.template import Context
from django.template.loader import get_template

# Create your views here.

'''
def main_page(request):
	template = get_template('main_page.html')
	variables = Context({
		'head_title': 'This is FIRST title',
		'page_title': 'Here is page title',
		'page_body': 'Here is page body',
	})
	output = template.render(variables)
	return HttpResponse(output)				
'''
#/* shortcut version */
def main_page(request):
				
	context={
		'head_title': 'This is FIRST title',
		'page_title': 'Here is page title',
		'page_body': 'Here is page body',
	}
	return render(request,'main_page.html',context)




