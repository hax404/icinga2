/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2017 Icinga Development Team (https://www.icinga.com/)  *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef GELFWRITER_H
#define GELFWRITER_H

#include "perfdata/gelfwriter.thpp"
#include "icinga/service.hpp"
#include "base/configobject.hpp"
#include "base/tcpsocket.hpp"
#include "base/timer.hpp"
#include <fstream>

namespace icinga
{

/**
 * An Icinga gelf writer.
 *
 * @ingroup perfdata
 */
class GelfWriter : public ObjectImpl<GelfWriter>
{
public:
	DECLARE_OBJECT(GelfWriter);
	DECLARE_OBJECTNAME(GelfWriter);

protected:
	virtual void Start(bool runtimeCreated) override;

private:
	Stream::Ptr m_Stream;

	Timer::Ptr m_ReconnectTimer;

	void CheckResultHandler(const Checkable::Ptr& checkable, const CheckResult::Ptr& cr);
	void NotificationToUserHandler(const Notification::Ptr& notification, const Checkable::Ptr& checkable,
	const User::Ptr& user, NotificationType notification_type, CheckResult::Ptr const& cr,
	const String& author, const String& comment_text, const String& command_name);
	String ComposeGelfMessage(const Dictionary::Ptr& fields, const String& source, double ts);
	void StateChangeHandler(const Checkable::Ptr& checkable, const CheckResult::Ptr& cr, StateType type);
	void SendLogMessage(const String& gelf);

	void ReconnectTimerHandler(void);
};

}

#endif /* GELFWRITER_H */
