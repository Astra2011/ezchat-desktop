/*
This file is part of PolySRV Desktop,
a Telegram Desktop fork for the PolySRV multi-server client.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "core/polysrv_remote.h"

#include "core/branding.h"

namespace PolySrv {

QString RemoteDomain() {
	return Branding::RemoteDomain.utf16();
}

QString ServersUrl() {
	return RemoteDomain() + u"/servers.json"_q;
}

QString UpdateManifestUrl() {
	return RemoteDomain() + u"/update.json"_q;
}

QString ServersFallbackUrl() {
	// EzChat is locked to a single built-in server and never fetches a
	// remote list, so there is deliberately no fallback URL.
	return QString();
}

} // namespace PolySrv
