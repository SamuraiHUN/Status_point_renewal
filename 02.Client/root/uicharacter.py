search this:

	def __OnClickStatusPlusButton(self, statusKey):
		try:
			statusPlusCommand=self.statusPlusCommandDict[statusKey]
			net.SendChatPacket(statusPlusCommand)
		except KeyError, msg:
			dbg.TraceError("CharacterWindow.__OnClickStatusPlusButton KeyError: %s", msg)

change to:

	def __OnClickStatusPlusButton(self, statusKey):
		try:
			if app.STATUS_UP_RENEWAL:
				if app.IsPressed(app.DIK_LCONTROL) or app.IsPressed(app.DIK_RCONTROL):
					status_inc = constInfo.INCREASE_POINTS_CTRL
				else:
					status_inc = 1

				statusPlusCommand=self.statusPlusCommandDict[statusKey]
				net.SendChatPacket("%s %d" % (statusPlusCommand, status_inc))
			else:
				statusPlusCommand=self.statusPlusCommandDict[statusKey]
				net.SendChatPacket(statusPlusCommand)

		except KeyError, msg:
			dbg.TraceError("CharacterWindow.__OnClickStatusPlusButton KeyError: %s", msg)

search this:

	def __ShowStatToolTip(self, statDesc):
		self.toolTip.ClearToolTip()
		self.toolTip.AppendTextLine(statDesc)
		self.toolTip.Show()

change to:

	def __ShowStatToolTip(self, statDesc):
		self.toolTip.ClearToolTip()
		self.toolTip.AppendTextLine(statDesc)
		self.toolTip.AppendSpace(5)
		self.toolTip.AppendTextLine("|Ekey/key_ctrl|e + |Ekey/key_lclick|e - " +\
								localeInfo.MULTIPLY_STATE_POINT_ADD_TEXT.format(constInfo.INCREASE_POINTS_CTRL),\
								constInfo.TOOLTIP_KEYS_COLOR_HEX)
		self.toolTip.Show()
