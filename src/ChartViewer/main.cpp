#include <QApplication>
#include <QMessageBox>
#include <QScrollBar>
#include <QTextEdit>
#include <QTimer>
#include <cppkafka/cppkafka.h>
#include <iostream>
#include <string>

std::unique_ptr<cppkafka::Consumer> consumer;

void dispatch(QTextEdit& textEdit) {
	QTimer* timer = new QTimer();
	timer->moveToThread(qApp->thread());

	QObject::connect(timer, &QTimer::timeout, [&textEdit]()
		{
			// main thread
			auto xs = consumer->poll_batch(1000, std::chrono::milliseconds(100));
			if (!xs.empty()) {
				for (const auto& x : xs) {
					auto k = std::string(x.get_key().begin(), x.get_key().end());
					auto s = std::string(x.get_payload().begin(), x.get_payload().end());
					textEdit.append(QString::fromStdString(k + " : " + s));
					
					//timer->deleteLater();
				}
				textEdit.verticalScrollBar()->setValue(textEdit.verticalScrollBar()->maximum());
			}
		});
	QMetaObject::invokeMethod(timer, "start", Qt::QueuedConnection, Q_ARG(int, 50));
}

int main(int argc, char **argv) try 
{
	QApplication app(argc, argv);
	cppkafka::Configuration config = {
		{"metadata.broker.list", "127.0.0.1:9093"  },
		{"group.id","my_topic"}
	};

	
	consumer = std::make_unique<cppkafka::Consumer>(config);
	consumer->subscribe({ "my_topic" });
	
	
	QTextEdit textEdit;
	textEdit.setText(QString("Log"));
	dispatch(textEdit);
	
	textEdit.resize(250, 150);
	textEdit.setWindowTitle("Simple example");
	textEdit.show();
	return app.exec();
}
catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
}