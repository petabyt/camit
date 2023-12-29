di = ptp.sendOperation(0xBEEF, {10}, {1, 2, 3, 4})
print(json.encode(di))
rc = ptp.setProperty("shutter speed", 12500)
