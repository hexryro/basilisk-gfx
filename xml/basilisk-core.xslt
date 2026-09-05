<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:include href="helpers.xsl"/>
	<xsl:variable name="vk" select="document('vk.xml')"/>

	<xsl:template match="@*|node()">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
	</xsl:template>

	<xsl:template name="replace-prefix">
		<xsl:param name="text"/>
		<xsl:param name="old"/>
		<xsl:param name="new"/>

		<xsl:choose>
			<xsl:when test="starts-with($text, $old)">
				<xsl:value-of select="$new"/>
				<xsl:value-of select="substring($text, string-length($old) + 1)"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$text"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	
	<xsl:template match="enum|serializableEnum" mode="vk-line">
		<xsl:param name="indent"/>

		<line>
			<name>
				<xsl:call-template name="replace-prefix">
					<xsl:with-param name="text" select="@name"/>
					<xsl:with-param name="old" select="'VK_'"/>
					<xsl:with-param name="new" select="'BS_'"/>
				</xsl:call-template>
			</name>

			<value>
				<xsl:choose>
					<xsl:when test="@value">
						<xsl:value-of select="@value"/>
					</xsl:when>

					<xsl:when test="@bitpos">
						<xsl:text>1 &lt;&lt; </xsl:text>
						<xsl:value-of select="@bitpos"/>
					</xsl:when>

					<xsl:otherwise>
						<xsl:text>0</xsl:text>
					</xsl:otherwise>
				</xsl:choose>
			</value>
		</line>
	</xsl:template>

	<xsl:template match="enum|serializableEnum" mode="vk-extends">
		<xsl:param name="indent"/>

		<line>
			<name>
				<xsl:call-template name="replace-prefix">
					<xsl:with-param name="text" select="@name"/>
					<xsl:with-param name="old" select="'VK_'"/>
					<xsl:with-param name="new" select="'BS_'"/>
				</xsl:call-template>
			</name>
			<value><xsl:value-of select="1000000000 + ((../../@number - 1) * 1000) + @offset"/></value>
		</line>
	</xsl:template>

	<xsl:template name="applyEnumExtensions">
		<xsl:param name="sourceEnum"/>
		
		<xsl:for-each select="/registry/extensions">
			<xsl:apply-templates select="$vk/registry/extensions/extension[@name = 'VK_KHR_swapchain']/require/enum[@extends = $sourceEnum]" mode="vk-extends"/>
		</xsl:for-each>
	</xsl:template>

	<xsl:template match="serializableEnum[@copyFrom]">
		<serializableEnum name="{@name}" deserialize="{@deserialize}" index="{@index}" count="{@count}">
			<xsl:variable name="sourceEnum" select="@copyFrom"/>
			<xsl:apply-templates select="$vk/registry/enums[@name = $sourceEnum]/enum" mode="vk-line"/>
			<xsl:call-template name="applyEnumExtensions"><xsl:with-param name="sourceEnum" select="$sourceEnum"/></xsl:call-template>
		</serializableEnum>
	</xsl:template>

	<xsl:template match="enum[@copyFrom]">
		<enum name="{@name}">
			<xsl:variable name="sourceEnum" select="@copyFrom"/>
			<xsl:apply-templates select="$vk/registry/enums[@name = $sourceEnum]/enum" mode="vk-line"/>
			<xsl:call-template name="applyEnumExtensions"><xsl:with-param name="sourceEnum" select="$sourceEnum"/></xsl:call-template>
		</enum>
	</xsl:template>

</xsl:stylesheet>
