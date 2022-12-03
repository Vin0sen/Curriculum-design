from PySide6.QtWidgets import QApplication,QTabWidget
from PySide6.QtUiTools import QUiLoader
'''
    单窗口, 多个子页面的切换
    - 利用 QStackedWidget 进行实现
    - 利用 QTabWidge      进行实现
    给按钮添加样式, 高亮当前页面对应的按钮
    - 思路: 绑定点击事件，点击前初始化所有按钮样式，然后高亮点击的按钮; 
    按钮数和页面数是相当的, 通过索引可以获取当前按钮, 从而修改样式
'''

class SubPages:
    def __init__(self) -> None:
        self.ui = QUiLoader().load("ui/demo4.ui")
        self.btn = [self.ui.btn_p1, self.ui.btn_p2]
        buttonText = ['Page1','Page2']
        
        for i in range(len(self.btn)):
            self.btn[i].setText(buttonText[i])
            self.btn[i].setStyleSheet(self.setBtnStyle())

        self.ui.stackedWidget.setCurrentIndex(0)
        self.ui.tabWidget.setCurrentIndex(0)
        self.btn[0].setStyleSheet(self.setBtnStyle(True))
        
        self.bind()

    def bind(self):
        self.btn[0].clicked.connect(lambda: self.changePage(0))
        self.btn[1].clicked.connect(lambda: self.changePage(1))

    def changePage(self,index:int):
        for btn in self.btn:
            btn.setStyleSheet(self.setBtnStyle())
        self.btn[index].setStyleSheet(self.setBtnStyle(click=True))
        self.ui.stackedWidget.setCurrentIndex(index)
    def setBtnStyle(self,click=False):
        if click==True:
            style = 'border:2px solid rgb(0, 255, 255);'
        else:
            style = 'border:1px solid rgba(204, 204, 204, 150);'
        return 'QPushButton{'+style+' border-radius:10px; } '


if __name__ == '__main__':
    app = QApplication([])
    tabs = SubPages()
    tabs.ui.tabWidget.setTabPosition(QTabWidget.West)
    tabs.ui.show()
    app.exec()

