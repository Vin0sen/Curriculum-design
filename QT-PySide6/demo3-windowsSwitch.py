from PySide6.QtWidgets import QPushButton,QApplication,QMainWindow
'''
    多个窗口间的切换 
    QWidgets.hide() / close() / show()
'''

class Windows1:
    def __init__(self) -> None:
        self.w = QMainWindow()
        self.w.resize(500,400)
        self.w.setWindowTitle("窗口一")

        self.button = QPushButton('你好世界', self.w)
        self.button.clicked.connect(self.opeNeWindow)

    def opeNeWindow(self):
        self.w2 = Windows2()  # 实例化另一窗口
        self.w2.w.show()  # 显示新窗口
        self.w.close()  # 关闭

class Windows2:
    def __init__(self) -> None:
        self.w = QMainWindow()
        self.w.resize(500,400)
        self.w.setWindowTitle("窗口二")
        self.button = QPushButton('helloWorld',self.w)
        self.button.clicked.connect(self.opeNeWindow)

    def opeNeWindow(self):
        self.w.close()  # 关闭
        mainWindow.w.show()  # 显示新窗口

if __name__ == '__main__':
    app = QApplication()
    mainWindow = Windows1()
    mainWindow.w.show()
    app.exec()