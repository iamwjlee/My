from django.contrib import admin
from blog.models import Entries, Categories, TagModel


# Register your models here.

admin.site.register(Categories)
admin.site.register(TagModel)
admin.site.register(Entries)
