#include "../incs/Interface.h"

int main() {

	Interface Inter;

	if (Inter.Construct(720, 480, 1, 1))
		Inter.Start();

	return 0;
}