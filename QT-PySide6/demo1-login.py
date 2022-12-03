from PySide6.QtWidgets import *
from PySide6.QtUiTools import QUiLoader

class Login:
    def __init__(self) -> None:
        self.ui = QUiLoader().load("ui/demo1.ui")
        self.ui.setWindowTitle("登录界面")
        self.ui.btn_login.clicked.connect(self.slot)
        self.ui.lineEdit_zh.setPlaceholderText("请输入账户名")
        self.ui.lineEdit_mm.setEchoMode(QLineEdit.Password)
    def slot(self):
        zhanghao = self.ui.lineEdit_zh.text()
        pwd = self.ui.lineEdit_mm.text()
        if zhanghao == 'admin' and pwd == 'admin':
            print("登录成功")
        else:
            QMessageBox.about(self.ui,'消息框','登录失败 (´▽`ʃ♡ƪ)')


if __name__ == '__main__':
    app = QApplication([])
    login = Login()
    login.ui.show()
    app.exec()