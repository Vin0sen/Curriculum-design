from PySide6.QtWidgets import QApplication
from PySide6.QtUiTools import QUiLoader
import requests, traceback
'''
https://blog.csdn.net/m0_52062236/article/details/128160126
'''
class HttpClient:
    def __init__(self) -> None:

        self.ui=QUiLoader().load('ui/demo2.ui')
        self.ui.methodBox.addItems(['GET','POST'])
        self.bind()
        
    def bind(self):  
        self.ui.btn_add.clicked.connect(self.addOneHeader)
        self.ui.btn_minus.clicked.connect(self.delOneHeader)
        self.ui.btn_send.clicked.connect(self.sendRequest)
    
    def addOneHeader(self):
        # rowCount = self.ui.headersTable.rowCount()
        # 要插入的行始终是当前行的下一行
        addRowNum = self.ui.headersTable.currentRow()+1
        self.ui.headersTable.insertRow(addRowNum)
    
    def delOneHeader(self):
        self.ui.headersTable.removeRow(self.ui.headersTable.currentRow())
    def sendRequest(self):
        method = self.ui.methodBox.currentText()
        url = self.ui.urlLineEdit.text()
        payload = self.ui.bodyText.toPlainText()

        headers = {}
        ht=self.ui.headersTable
        for row in range(ht.rowCount()):
            if not ht.item(row,0):
                continue
            k=ht.item(row,0).text().strip()
            v=ht.item(row,1).text().strip()
            headers[k] = v
        
        req = requests.Request(method,url,headers=headers,data=payload)
        prepared = req.prepare()

        # self.pretty_print_request(prepared)
        s = requests.Session()

        try:
            r = s.send(prepared)
            self.pretty_print_response(r)
        except:
            self.ui.responseText.append(traceback.format_exc())
        
    def pretty_print_response(self,res):
        self.ui.responseText.append(
            '{}\nHTTP/1.1 {}\n{}\n\n{}'.format(
            '\n\n----------- 得到响应 -----------',
            res.status_code,
            '\n'.join('{}: {}'.format(k, v) for k, v in res.headers.items()),
            res.text,
            ))


if __name__ == '__main__':
    app = QApplication([])
    stats = HttpClient()
    stats.ui.show()
    app.exec()
            
