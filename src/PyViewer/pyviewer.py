import random
from itertools import count
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from kafka import KafkaConsumer
import sys
plt.style.use('fivethirtyeight')

x_values = []
y_values = []

index = count()


def animate(i):
    count = 0;
  
    try:
        for message in consumer:
            
            x_values.append(next(index))
            y_values.append(message.value)
        
            print ("%s:%d:%d: key=%s value=%s" % (message.topic, message.partition,message.offset, message.key,message.value))
            count = count + 1
            if count > 100:
                return
    except KeyboardInterrupt:
        sys.exit()
   
    plt.cla()
    plt.plot(x_values, y_values)




ani = FuncAnimation(plt.gcf(), animate, 1000000)

bootstrap_servers = ['localhost:9093']
topicName = 'drone3'
consumer = KafkaConsumer (topicName, group_id = 'group1',bootstrap_servers = bootstrap_servers,
auto_offset_reset = 'earliest')

plt.tight_layout()
plt.show()