/*
This file is part of PolySRV Desktop,
a Telegram Desktop fork for the PolySRV multi-server client.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "intro/intro_step.h"

#include "base/timer.h"
#include "polysrv/polysrv_servers.h"
#include "ui/layers/box_content.h"

#include <QtCore/QPointer>

namespace Ui {
class BoxContent;
class FlatLabel;
class RoundButton;
class RpWidget;
class ScrollArea;
} // namespace Ui

namespace Intro {
namespace details {

// Shown while the client connects to the built-in EzChat server, before the
// login step. Reused by the start widget so there is no server selection UI.
class ConnectingBox final : public Ui::BoxContent {
public:
	ConnectingBox(
		QWidget *,
		not_null<Main::Account*> account,
		const QString &serverName,
		Fn<void()> ready);

protected:
	void prepare() override;

private:
	void poll();
	void showFailed();
	void updateText();

	const not_null<Main::Account*> _account;
	const QString _serverName;
	Fn<void()> _ready;
	QPointer<Ui::FlatLabel> _label;
	QPointer<Ui::RoundButton> _button;
	base::Timer _poll;
	base::Timer _dots;
	crl::time _started = 0;
	int _dotsCount = 0;
	bool _failed = false;
	bool _finished = false;
};

// The step that chooses the server an account signs in to.
class ServerSelectWidget final : public Step {
public:
	ServerSelectWidget(
		QWidget *parent,
		not_null<Main::Account*> account,
		not_null<Data*> data);

	void finishInit() override;
	void activate() override;
	void submit() override;
	[[nodiscard]] bool hasBack() const override;
	[[nodiscard]] rpl::producer<QString> nextButtonText() const override;

	void resizeEvent(QResizeEvent *e) override;

private:
	void rebuildList();
	void showDetails(const PolySrv::Server &server);
	void joinServer(const PolySrv::Server &server);
	void proceedJoin(const PolySrv::Server &server);
	void updateListGeometry();
	void updateRowsGeometry();
	void updateStatus();
	[[nodiscard]] int listWidth() const;
	[[nodiscard]] int listInnerWidth() const;
	[[nodiscard]] int listPanelHeight(int panelTop) const;

	QPointer<Ui::RpWidget> _panel;
	QPointer<Ui::ScrollArea> _scroll;
	QPointer<Ui::RpWidget> _rowsContainer;
	QPointer<Ui::FlatLabel> _ownTitle;
	QPointer<Ui::FlatLabel> _ownDescription;
	QPointer<Ui::FlatLabel> _status;
	object_ptr<Ui::RoundButton> _addServer;
};

} // namespace details
} // namespace Intro
