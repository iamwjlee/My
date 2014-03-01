from django.http import HttpResponse,HttpResponseRedirect
from django.shortcuts import render

from survey.model import Vote
# Create your views here.
#http://www.thecodertips.com/2014/02/simple-forms-with-python-and-django.html
def surveyDisplay(request):
				return render(request,'survey/display.html')
def surveyProcess(request):
				Vote(choiceDay = request.POST['day'],
				choiceTime = int(request.POST['time']),
				voterName =request.POST['name']).save()								
				return HttpResponseRedirect("results")



