#include "PacketLogger.h"

PacketLogger::PacketLogger() : IModule(0x0, Category::WORLD, "Logs packets, PacketAddr shows the CE or IDA address for packet, AuthChunk shows PAIP and SCRP and SetTitle shows STP") {
	registerEnumSetting("Packet Type", &packetType, 0);
	packetType = SettingEnum(this)
			.addEntry(EnumEntry("Server", 0))
			.addEntry(EnumEntry("Client", 1));
	registerBoolSetting("SetTitle", &setTitle, setTitle);
	registerBoolSetting("Packet Addr", &packetadd, &packetadd);
	registerBoolSetting("Auth & Chunk", &authchunk, authchunk);
	registerEnumSetting("Mode", &addressType, 0);
	addressType = SettingEnum(this)
			.addEntry(EnumEntry("CE Address", 0))
			.addEntry(EnumEntry("IDA Address", 1));
}

PacketLogger::~PacketLogger() {}

const char* PacketLogger::getModuleName() {
	return "PacketLogger";
}

void PacketLogger::onSendPacket(Packet* packet) {
	if (packetType.selected == 0) {
		LocalPlayer* player = Game.getLocalPlayer();
		if (player != nullptr) {
			uint64_t currVTable = *(UINT64*)packet;
			std::stringstream stream;
			if (packetadd && addressType.selected == 0) {
				if (!authchunk && (strcmp(packet->getName()->getText(), "PlayerAuthInputPacket") == 0 || strcmp(packet->getName()->getText(), "SubChunkRequestPacket") == 0)) {
					return;
				}
				stream << std::hex << (currVTable - Utils::getBase());
				std::string result(stream.str());
				std::string packetText = packet->getName()->getText() + (std::string) " (Minecraft.Windows.exe+" + result + ")";
				TextHolder txt = TextHolder(packetText);
				player->displayClientMessage(&txt);
			}
			if (packetadd && addressType.selected == 1) {
				if (!authchunk && (strcmp(packet->getName()->getText(), "PlayerAuthInputPacket") == 0 || strcmp(packet->getName()->getText(), "SubChunkRequestPacket") == 0)) {
					return;
				}
				stream << std::hex << (currVTable - Utils::getBase() + 0x140000000);
				std::string result(stream.str());
				std::string packetText = packet->getName()->getText() + std::string(" = ") + result;
				TextHolder txt = TextHolder(packetText);
				player->displayClientMessage(&txt);
			}

			if (!authchunk) {
				if (!packetadd) {
					if (strcmp(packet->getName()->getText(), "PlayerAuthInputPacket") != 0 && strcmp(packet->getName()->getText(), "SubChunkRequestPacket") != 0) {
						Game.getClientInstance()->getGuiData()->displayClientMessageF("%s", packet->getName()->getText());
					}
				}
			} else {
				Game.getClientInstance()->getGuiData()->displayClientMessageF("%s", packet->getName()->getText());
			}
		}
	}
}

void PacketLogger::onSendClientPacket(Packet* packet) {
	if (packetType.selected == 1) {
		LocalPlayer* player = Game.getLocalPlayer();
		if (player != nullptr) {
			uint64_t currVTable = *(UINT64*)packet;
			std::stringstream stream;
			if (packetadd && addressType.selected == 0) {
				if (!setTitle && (strcmp(packet->getName()->getText(), "SetTitlePacket") == 0)) {
					return;
				}
				stream << std::hex << (currVTable - Utils::getBase());
				std::string result(stream.str());
				std::string packetText = packet->getName()->getText() + (std::string) " (Minecraft.Windows.exe+" + result + ")";
				TextHolder txt = TextHolder(packetText);
				player->displayClientMessage(&txt);
			}
			if (packetadd && addressType.selected == 1) {
				if (!setTitle && (strcmp(packet->getName()->getText(), "SetTitlePacket") == 0)) {
					return;
				}
				stream << std::hex << (currVTable - Utils::getBase() + 0x140000000);
				std::string result(stream.str());
				std::string packetText = packet->getName()->getText() + std::string(" = ") + result;
				TextHolder txt = TextHolder(packetText);
				player->displayClientMessage(&txt);
			}

			if (!setTitle) {
				if (!packetadd) {
					if (strcmp(packet->getName()->getText(), "SetTitlePacket") != 0) {
						Game.getClientInstance()->getGuiData()->displayClientMessageF("%s", packet->getName()->getText());
					}
				}
			} else {
				Game.getClientInstance()->getGuiData()->displayClientMessageF("%s", packet->getName()->getText());
			}
		}
	}
}