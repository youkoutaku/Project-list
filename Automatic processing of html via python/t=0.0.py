from bs4 import BeautifulSoup

# 读取HTML文件
with open('example.html') as f:
    html = f.read()

# 解析HTML文件
soup = BeautifulSoup(html, 'html.parser')

# 添加div元素
new_div = soup.new_tag('div')
new_div.string = 'This is a new div'
soup.body.append(new_div)

# 保存修改后的HTML文件
with open('example_modified.html', 'w') as f:
    f.write(str(soup))
