from django.conf.urls import patterns, include, url

from django.contrib import admin

from first.views import *

admin.autodiscover()

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'dj02.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),
		url(r'^$', main_page),
    url(r'^admin/', include(admin.site.urls)),
)
