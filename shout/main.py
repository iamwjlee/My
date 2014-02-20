#!/usr/bin/env python

#print 
#print 'Hello world'a

import wsgiref.handlers
from google.appengine.ext import webapp
from google.appengine.ext import db

from google.appengine.ext.webapp import template

class Shout(db.Model):
	message = db.StringProperty(required=True)
	when = db.DateTimeProperty(auto_now_add=True)
	who = db.StringProperty()

class MyHandler(webapp.RequestHandler):
	def get(self):
		#shouts = db.GqlQuery(	'SELECT * FROM Shout'	'ORDER BY when DESC')
		shouts = db.GqlQuery(	'SELECT * FROM Shout')
		values = { 'shouts': shouts }
		self.response.out.write( unicode(template.render('main.html', values)))
		#self.response.out.write( unicode(template.render('main.html', {})))
		#self.response.out.write("hello !")
	def post(self):
		shout = Shout(message=self.request.get( 'message'), who=self.request.get('who'))
		shout.put()
		#self.response.out.write('posted!')
		self.redirect('/')

def main():
	app = webapp.WSGIApplication([
				(r'.*',MyHandler)], debug=True)

	wsgiref.handlers.CGIHandler().run(app)


if __name__ == "__main__":
	main()

