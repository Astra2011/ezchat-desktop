/*
This file is part of PolySRV Desktop,
a Telegram Desktop fork for the PolySRV multi-server client.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "base/basic_types.h"

#include <QtCore/QString>

namespace PolySrv {

// The shapes of a ez:// link.
struct Link {
	enum class Type {
		// Not a link we know.
		Unknown,
		// ez://addserver?host=..&port=.. -- record a server.
		AddServer,
		// ez://oauth?.. and ez://resolve?.. -- a command.
		Command,
		// ez://<server host>/<rest> -- a link of one server.
		ServerHost,
	};

	Type type = Type::Unknown;
	// The host and the port of the server of an AddServer link.
	QString host;
	int port = 0;
	// The command of a Command link, without the question mark.
	QString command;
	// The server host and the rest of a ServerHost link.
	QString serverHost;
	QString rest;
};

[[nodiscard]] Link ParseLink(const QString &url);

} // namespace PolySrv
