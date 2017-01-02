import sys
a = open(sys.argv[1],'r')
for b in a:
    try:
            print b.decode('gbk').encode('gb2312').decode('gb2312'),
    except:
            pass
