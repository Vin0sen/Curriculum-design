from PySide6.QtWidgets import QApplication
from PySide6.QtUiTools import QUiLoader
class ToolKit:
    def __init__(self) -> None:
        self.ui = QUiLoader().load("ui/demo5.ui")
        self.ui.setWindowTitle("ToolKit")
        self.btnMenu = [self.ui.BtnMenu0, self.ui.BtnMenu1, self.ui.BtnMenu2, self.ui.BtnMenu3]
        
        for btn in self.btnMenu:
            btn.setStyleSheet(self.setBtnStyle())

        self.ui.stackedWidget.setCurrentIndex(0)
        self.btnMenu[0].setStyleSheet(self.setBtnStyle(True))
        
        self.bind()

    def bind(self):
        self.btnMenu[0].clicked.connect(lambda: self.changePage(0))
        self.btnMenu[1].clicked.connect(lambda: self.changePage(1))
        self.btnMenu[2].clicked.connect(lambda: self.changePage(2))
        self.btnMenu[3].clicked.connect(lambda: self.changePage(3))
        self.BtnDirsearch.clicked.connect()

    def changePage(self,index:int):
        for btn in self.btnMenu:
            btn.setStyleSheet(self.setBtnStyle())
        self.btnMenu[index].setStyleSheet(self.setBtnStyle(click=True))
        self.ui.stackedWidget.setCurrentIndex(index)
    def setBtnStyle(self,click=False):
        if click==True:
            style = 'border:2px solid rgb(0, 255, 255);'
        else:
            style = 'border:1px solid rgba(204, 204, 204, 150);'
        return 'QPushButton{'+style+' border-radius:10px; } '


if __name__ == '__main__':
    app = QApplication([])
    window = ToolKit()
    window.ui.show()
    app.exec()