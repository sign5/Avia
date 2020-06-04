#include "mainwindow.h"
#include <QApplication>


void seg_handler(int signal) {
    std::cerr << "Programm was terminated\n";
    exit(signal);
}

void std_handler(void) {
     seg_handler(1);
}

void myunexpected () {
  std::cerr << "unexpected called\n";
  throw 0;     // throws int (in exception-specification)
}

void myfunction () throw (int) {
  throw 'x';   // throws char (not in exception-specification)
}

int main(int argc, char *argv[]) {
    std::set_terminate(std_handler);
    std::set_unexpected(myunexpected);

//    throw std::exception(); // Для примера c set_terminate, set_unexpected
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
