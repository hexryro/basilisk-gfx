<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:include href="helpers.xsl"/>

	<xsl:template match="@*|node()">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
	</xsl:template>

	<xsl:template match="variadicStringTemplate">
		<function name="{@name}N">
			<xsl:copy-of select="return | param"/>
			<xsl:choose>
				<xsl:when test="@string">
					<param><type>char*</type><name><xsl:value-of select="@string"/></name></param>
					<param><type>int</type><name><xsl:value-of select="@string"/>_length</name></param>
				</xsl:when>
				<xsl:otherwise>
					<param><type>char*</type><name>value</name></param>
					<param><type>int</type><name>value_length</name></param>
				</xsl:otherwise>
			</xsl:choose>
		</function>

		<function name="{@name}" type="allowBody">
			<xsl:copy-of select="return | param"/>

			<xsl:variable name="string">
				<xsl:choose>
					<xsl:when test="@string">
						<xsl:value-of select="@string"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="'value'"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>

			<param><type>char*</type><name><xsl:value-of select="$string"/></name></param>
			<body>
				<xsl:text>    </xsl:text>
				<xsl:if test="not(return = 'void')">
					<xsl:text>return </xsl:text>
				</xsl:if>

				<xsl:text>_</xsl:text>
				<xsl:value-of select="@name"/>
				<xsl:text>N(</xsl:text>
				<xsl:for-each select="param">
					<xsl:value-of select="name"/>
					<xsl:text>, </xsl:text>
				</xsl:for-each>
				<xsl:value-of select="$string"/>
				<xsl:text>, strlen(</xsl:text>
				<xsl:value-of select="$string"/>
				<xsl:text>));</xsl:text>
			</body>
		</function>
		
		<function name="{@name}V" type="allowBody">
			<xsl:copy-of select="return | param"/>
			<param>
				<type>char*</type>
				<name>format</name>
			</param>
			<param>
				<type>va_list</type>
				<name>args</name>
			</param>
			<body>
				<xsl:text>    int _length = bs_formatStringLength(format, args);&#xA;</xsl:text>
				<xsl:text>    char* _formatted = bs_alloca(_length + 1);&#xA;</xsl:text>
				<xsl:text>    vsnprintf(_formatted, _length + 1, format, args);&#xA;</xsl:text>

				<xsl:text>    </xsl:text>
				<xsl:if test="not(return = 'void')">
					<xsl:text>return </xsl:text>
				</xsl:if>

				<xsl:text>_</xsl:text>
				<xsl:value-of select="@name"/>
				<xsl:text>N(</xsl:text>
				<xsl:for-each select="param">
					<xsl:value-of select="name"/>
					<xsl:text>, </xsl:text>
				</xsl:for-each>
				<xsl:text>_formatted, _length);</xsl:text>
			</body>
		</function>

		<function name="{@name}F" type="allowBody">
			<xsl:copy-of select="return | param"/>
			<param>
				<type>char*</type>
				<name>format</name>
			</param>
			<param>
				<name>...</name>
			</param>
			<body>
				<xsl:text>    va_list args;&#xA;</xsl:text>
				<xsl:text>    va_start(args, format);&#xA;</xsl:text>

				<xsl:text>    </xsl:text>
				<xsl:if test="not(return = 'void')">
					<xsl:value-of select="return"/>
					<xsl:text> _return = </xsl:text>
				</xsl:if>

				<xsl:text>_</xsl:text>
				<xsl:value-of select="@name"/>
				<xsl:text>V(</xsl:text>
				<xsl:for-each select="param">
					<xsl:value-of select="name"/>
					<xsl:text>, </xsl:text>
				</xsl:for-each>
				<xsl:text>format, args</xsl:text>

				<xsl:text>);&#xA;    va_end(args);</xsl:text>

				<xsl:if test="not(return = 'void')">
					<xsl:text>&#xA;    return _return;</xsl:text>
				</xsl:if>


			</body>
		</function>
	</xsl:template>

</xsl:stylesheet>
