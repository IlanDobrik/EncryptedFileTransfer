#include "TransferInfo.hpp"
#include "Me.hpp"

#define TRANSFER_INFO_PATH "./transfer.info"
#define ME_PATH "./me.info"


int main(void) {
    auto config = getTransferInfo(TRANSFER_INFO_PATH);
    auto me = getMe(ME_PATH);

    return 0;
};