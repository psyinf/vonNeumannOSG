#include <QApplication>
#include <QMessageBox>
#include <QScrollBar>
#include <QTextEdit>
#include <QTimer>
#include <QChart>
#include <QLineSeries>
#include <QMainWindow>
#include <QChartView>
#include <QXYSeries>
#include <QValueAxis>
#include <cppkafka/cppkafka.h>
#include <iostream>
#include <string>

std::unique_ptr<cppkafka::Consumer> consumer;

void dispatch(QTextEdit& textEdit, QLineSeries* lines, QChartView* chartView) try{
	QTimer* timer = new QTimer();
	timer->moveToThread(qApp->thread());

	QObject::connect(timer, &QTimer::timeout, [&]()
		{
			// main thread
			auto xs = consumer->poll_batch(1000, std::chrono::milliseconds(100));
			if (!xs.empty()) {
				for (const auto& x : xs) {
					auto k = std::string(x.get_key().begin(), x.get_key().end());
					auto s = std::string(x.get_payload().begin(), x.get_payload().end());
					textEdit.append(QString::fromStdString(k + " : " + s));
                    auto p = QPointF(static_cast<float>(lines->count()), std::stof(x.get_payload()));
                    lines->append(p);
                    std::cout << ",";
				
				}
				textEdit.verticalScrollBar()->setValue(textEdit.verticalScrollBar()->maximum());
                chartView->update();
                std::cout << ".";
            
			}
		});
	QMetaObject::invokeMethod(timer, "start", Qt::QueuedConnection, Q_ARG(int, 50));
}
catch (const std::exception& e)
{
    std::cerr << e.what();
}
auto setupChart( QLineSeries* series)
{
    auto chart = new QChart();
    chart->legend()->hide();
   

	series->setUseOpenGL(true);
    auto axisX = new QValueAxis;
    auto axisY = new QValueAxis;
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
	

	

	return chart;
}
	int main(int argc, char **argv) try 
{
	QApplication app(argc, argv);
	cppkafka::Configuration config = {
		{"metadata.broker.list", "127.0.0.1:9093"  },
		{"group.id","1"}
	};
    QLineSeries*   simpleGLSeries = new QLineSeries;
    std::cout << simpleGLSeries->count();
    simpleGLSeries->replace(QList<QPointF>({}));
    
    QChartView* chartView = new QChartView(setupChart(simpleGLSeries));
	
	consumer = std::make_unique<cppkafka::Consumer>(config);
	consumer->subscribe({ "drone1" });
    
	QTextEdit textEdit;
	textEdit.setText(QString("Log"));
    dispatch(textEdit, simpleGLSeries, chartView);
	
	textEdit.resize(250, 150);
	textEdit.setWindowTitle("Simple example");
	textEdit.show();
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(600, 400);
    window.show();
	return QApplication::exec();
}
catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
}