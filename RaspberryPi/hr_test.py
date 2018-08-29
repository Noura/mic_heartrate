import heartbeat as hb

data = hb.get_data('heartbeat/data.csv')
measures = hb.process(data, 100.0)

print measures['bpm']
