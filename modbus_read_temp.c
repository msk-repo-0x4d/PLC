#include <stdio.h>
#include <stdlib.h>
#include "modbus-rtu.h"

int main()
{
    printf("Starting Modbus...");
    modbus_t * ctx;

    ctx = modbus_new_rtu("COM6", 19200, 'N', 8, 2);

    if (ctx == NULL) {
        fprintf(stderr, "Unable to create the libmodbus context\n");
        return -1;
    }

    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    modbus_set_debug(ctx, 1);
    modbus_set_slave(ctx, 1);

    const int NUM_REGS = 2;
    uint16_t tab_reg[NUM_REGS];
    // Read 2 registers from address 0 of server ID 10.
    int read_regs = modbus_read_registers(ctx, 1536, NUM_REGS, tab_reg);

    if(read_regs != NUM_REGS) {
        fprintf(stderr, "Failed to read %d registers.Read registers %d -- %s\n",
                 NUM_REGS, read_regs, modbus_strerror(errno));
        return -1;
    }

    printf("Number of registers read %d\nValues are shown below:\n", read_regs);
    for(int i = 0; i < NUM_REGS; ++i) {
        printf("%lld\n", *(tab_reg + i));
    }

    modbus_close(ctx);
    return 0;
}
