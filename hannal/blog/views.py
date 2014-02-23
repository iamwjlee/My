# -*- coding: utf-8 -*-
#from django.core.context_processors import csrf
from django.http import HttpResponse
from blog.models import Entries, Categories, TagModel
from django.template import Context, loader
from django.template import RequestContext, loader

def index(request, page=1):
    per_page = 5
    start_pos = (page - 1) * per_page
    end_pos = start_pos + per_page
    
    page_title = '블로그 글 목록 화면'
    
    entries = Entries.objects.select_related().all().order_by('-created')[start_pos:end_pos]

    tpl = loader.get_template('list.html')
    ctx = Context({
        'page_title':page_title,
        'entries':entries,
        'current_page':page
    })
    return HttpResponse(tpl.render(ctx))


def add_post(request):
    # 글 제목 처리
    if request.POST.has_key('title') == False:
        return HttpResponse('글 제목을 입력해야 한다우.')
    else:
        if len(request.POST['title']) == 0:
            return HttpResponse('글 제목엔 적어도 한 글자는 넣자!')
        else:
            entry_title = request.POST['title']

    # 글 본문 처리
    if request.POST.has_key('content') == False:
        return HttpResponse('글 본문을 입력해야 한다우.')
    else:
        if len(request.POST['content']) == 0:
            return HttpResponse('글 본문엔 적어도 한 글자는 넣자!')
        else:
            entry_content = request.POST['content']

    # 글 갈래 처리
    if request.POST.has_key('category') == False:
        return HttpResponse('글 갈래를 골라야 한다우.')
    else:
        try:
            entry_category = Categories.objects.get(id=request.POST['category'])
        except:
            return HttpResponse('이상한 글 갈래구려')

    # 글 꼬리표 처리
    if request.POST.has_key('tags') == True:
        tags = map(lambda str: str.strip(), unicode(request.POST['tags']).split(','))
        tag_list = map(lambda tag: TagModel.objects.get_or_create(Title=tag)[0], tags)
    else:
        tag_list = []
    
    # 꼬리표 저장을 위해 임시 저장
    new_entry = Entries(Title=entry_title, Content=entry_content, Category=entry_category)
    try:
        new_entry.save()
    except:
        return HttpResponse('글을 써넣다가 오류가 발생했습니다.')
    
    # 꼬리표 추가
    for tag in tag_list:
        new_entry.Tags.add(tag)
        
    # 최종 저장.
    if len(tag_list) > 0:
        try:
            new_entry.save()
        except:
            return HttpResponse('글을 써넣다가 오류가 발생했습니다.')

    return HttpResponse('%s번 글을 제대로 써넣었습니다.' % new_entry.id)


def write_form(request):
    page_title = '블로그 글 쓰기 화면'
    
    categories = Categories.objects.all()
    tpl = loader.get_template('write.html')
    ctx = Context({
        'page_title':page_title,
        'categories':categories
    })
    return HttpResponse(tpl.render(ctx))


def read(request, entry_id=None):
    page_title = '블로그 글 읽기 화면'
    
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
