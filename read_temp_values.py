
from pymodbus.client import ModbusSerialClient

client = ModbusSerialClient(
    method='rtu',
    port='COM6',
    baudrate=19200,
    timeout=5,
    parity='N',
    stopbits=2,
    bytesize=8
)


if client.connect():  # Trying for connect to Modbus Server/Slave
    '''Reading from a holding register'''

    for i in range(1536, 1538, 1):
        print('read_holding_registers - ' + str(i))
        '''Reading from holding register with the below content.'''
        res = client.read_holding_registers(address=i, count=1, slave=0x01, unit=1)

        if not res.isError():
            print(res.registers)
        else:
            print("xxxxxxxxxxErrorxxxxxxxxxx")
            print(res)

    client.close()
else:
    print('Cannot connect to the Modbus Server/Slave')
