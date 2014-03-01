from django.db import models

# Create your models here.


class Vote(models.Model):
				choiceDay = models.CharField(max_length=100)
				choiceTime = models.IntegerField()
				voterName = models.CharField(max_length=100)



