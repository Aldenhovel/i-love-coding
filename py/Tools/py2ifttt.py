import py2ifttt
from py2ifttt import IFTTT

msg = """
hello world
"""

key = r"your key of ifttt"
event_name = r"test"

ifttt = IFTTT(key=key, event_name=event_name)
ifttt.notify(value1=msg)