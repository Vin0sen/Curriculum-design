from PySide6.QtWidgets import QApplication
from PySide6.QtUiTools import QUiLoader

class Scroll:
    def __init__(self) -> None:
        self.ui = QUiLoader().load("ui/demo5.ui")
        

if __name__ == '__main__':
    app = QApplication([])
    tabs = Scroll()
    tabs.ui.show()
    app.exec()