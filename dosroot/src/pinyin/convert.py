import sys
a = open(sys.argv[1],'r')
c = []
for b in a:
    try:
            c.append(b.decode('gbk').encode('gb2312').decode('gb2312').replace("\n","").replace("\r",""))
    except UnicodeEncodeError:
            pass
d = open(sys.argv[1].split('/')[-1], 'w')
d.write("\n".join(c).encode("gb2312"))
