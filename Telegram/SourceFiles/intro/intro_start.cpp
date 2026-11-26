/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "core/branding.h"
#include "intro/intro_start.h"

#include "lang/lang_keys.h"
#include "boxes/abstract_box.h"
#include "intro/intro_qr.h"
#include "intro/intro_server_select.h"
#include "intro/intro_phone.h"
#include "polysrv/polysrv_servers.h"
#include "ui/layers/box_content.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/labels.h"
#include "main/main_account.h"
#include "main/main_app_config.h"

namespace Intro {
namespace details {

StartWidget::StartWidget(
	QWidget *parent,
	not_null<Main::Account*> account,
	not_null<Data*> data)
: Step(parent, account, data, true) {
	setMouseTracking(true);
	setTitleText(rpl::single(Branding::AppName.utf16()));
	setDescriptionText(tr::lng_intro_about());
	show();
}

void StartWidget::submit() {
	account().destroyStaleAuthorizationKeys();

	// EzChat is locked to a single built-in server: skip the server
	// selection step and connect straight to our own backend.
	const auto servers = PolySrv::Servers();
	if (servers.empty()) {
		return;
	}
	const auto &server = servers.front();
	account().applyServer(
		server.id,
		server.primaryHost(),
		server.primaryPort());
	Ui::show(
		Box<ConnectingBox>(
			&account(),
			server.name,
			crl::guard(this, [=] { goNext<QrWidget>(); })),
		Ui::LayerOption::KeepOther);
}

rpl::producer<QString> StartWidget::nextButtonText() const {
	return tr::lng_start_msgs();
}

rpl::producer<> StartWidget::nextButtonFocusRequests() const {
	return _nextButtonFocusRequests.events();
}

void StartWidget::activate() {
	Step::activate();
	setInnerFocus();
}

void StartWidget::setInnerFocus() {
	_nextButtonFocusRequests.fire({});
}

} // namespace details
} // namespace Intro
