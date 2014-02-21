from django.shortcuts import render

# Create your views here.
# -*- coding: utf-8 -*-
from django.http import HttpResponse
from blog.models import Entries
#from blog.models import Entries
from django.template import Context, loader

def index(request, page=1):
    page = int(page)				
    per_page = 5
    start_pos = (page - 1) * per_page
    end_pos = start_pos + per_page
    
    page_title = 'Blog contents window'
    
    entries = Entries.objects.select_related().all().order_by('-created')[start_pos:end_pos]

    tpl = loader.get_template('list.html')
    ctx = Context({
        'page_title':page_title,
        'entries':entries,
        'current_page':page
    })
    return HttpResponse(tpl.render(ctx))



def read(request, entry_id=None):
    page_title = 'Blog contents read window'
    
    current_entry = Entries.objects.get(id=int(entry_id))
    
    try:
        prev_entry = current_entry.get_previous_by_created()
    except:
        prev_entry = None
    
    try:
        next_entry = current_entry.get_next_by_created()
    except:
        next_entry = None
    
    tpl = loader.get_template('read.html')
    ctx = Context({
        'page_title':page_title,
        'current_entry':current_entry,
        'prev_entry':prev_entry,
        'next_entry':next_entry
    })
    return HttpResponse(tpl.render(ctx))

