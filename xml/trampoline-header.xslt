<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:include href="helpers.xsl"/>

    <xsl:output method="text"/>

    <xsl:strip-space elements="*"/>

    <xsl:variable name="prefix" select="registry/prefix"/>
    <xsl:variable name="spaces" select="'                                                                               '"/>
    <xsl:variable name="functionPrefix" select="registry/functionPrefix"/>
	<xsl:variable name="functionPrefixCaps" select="registry/functionPrefixCaps"/>

	<xsl:template match="/">
        <xsl:call-template name="add-license"/>

		<xsl:apply-templates select="registry/name"/>
		<xsl:apply-templates select="registry/includes/trampolineHeader/include"/>
		<xsl:text>&#xA;</xsl:text>
		<xsl:apply-templates select="registry/structures/*" mode="declaration"/>
        <xsl:text>&#xA;</xsl:text>
        <xsl:apply-templates select="registry/enums/enum" mode="declaration"/>
        <xsl:text>&#xA;</xsl:text>
        <xsl:apply-templates select="registry/macros/*"/>
        <xsl:apply-templates select="registry/typedefs/*"/>
		<xsl:apply-templates select="registry/enums/enum" mode="definition"/>
		<xsl:apply-templates select="registry/structures/*" mode="definition"/>
        <xsl:apply-templates select="registry/functions/*"/>
        <xsl:apply-templates select="registry/externs/*"/>

        <xsl:text>&#xA;#endif&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="registry/name">
#ifndef <xsl:value-of select="."/>
#define <xsl:value-of select="."/>
    <xsl:text>&#xA;&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="registry/includes/trampolineHeader/include">
        <xsl:text>#include &lt;</xsl:text>
        <xsl:value-of select="."/>
        <xsl:text>&gt;&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="registry/structures/structure" mode="declaration">
        <xsl:text>typedef </xsl:text>
        <xsl:choose>
            <xsl:when test="@type = 'union'">
                <xsl:text>union </xsl:text>
            </xsl:when>
            <xsl:otherwise>
                <xsl:text>struct </xsl:text>
            </xsl:otherwise>
        </xsl:choose>
        <xsl:value-of select="@name"/>
        <xsl:text> </xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text>;&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="registry/enums/enum" mode="declaration">
        <xsl:text>typedef enum </xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text> </xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text>;&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="define|ifdef|ifndef|elifdef|else|endif" mode="definition">
        <xsl:call-template name="addDirectives"/>
    </xsl:template>

    <xsl:template match="define|ifdef|ifndef|elifdef|else|endif">
        <xsl:call-template name="addDirectives"/>
    </xsl:template>

    <xsl:template match="macro">
        <xsl:value-of select="name"/>
        <xsl:value-of select="substring($spaces, 1, 68 - string-length(name))"/>
        <xsl:text> \&#xA;</xsl:text>
        <xsl:for-each select="line">
            <xsl:text>    </xsl:text>
            <xsl:value-of select="."/>
            <xsl:if test="position() != last()">
                <xsl:value-of select="substring($spaces, 1, 64 - string-length(.))"/>
                <xsl:text> \&#xA;</xsl:text>
            </xsl:if>
        </xsl:for-each>
        <xsl:text>&#xA;</xsl:text>

        <xsl:if test="not(parent::ifdef|parent::ifndef|parent::elifdef|parent::else)">
            <xsl:text>&#xA;</xsl:text>
        </xsl:if>
    </xsl:template>

    <xsl:template match="registry/typedefs/typedef">
        <xsl:text>typedef </xsl:text>
        <xsl:value-of select="type"/>
        <xsl:text> </xsl:text>
        <xsl:value-of select="name"/>
        <xsl:text>;&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="structure" mode="definition">
        <xsl:param name="indent" select="''"/>
        <xsl:value-of select="$indent"/>

        <xsl:choose>
            <xsl:when test="@type = 'union'">
                <xsl:text>union</xsl:text>
            </xsl:when>
            <xsl:otherwise>
                <xsl:text>struct</xsl:text>
            </xsl:otherwise>
        </xsl:choose>

        <xsl:if test="@name">
            <xsl:text> </xsl:text>
            <xsl:value-of select="@name"/>
        </xsl:if>
        <xsl:text> {&#xA;</xsl:text>

        <xsl:apply-templates select="*" mode="definition">
            <xsl:with-param name="indent" select="concat($indent, '    ')"/>
        </xsl:apply-templates>

        <xsl:value-of select="$indent"/>
        <xsl:text>}</xsl:text>
        <xsl:value-of select="@instance"/>
        <xsl:text>;&#xA;</xsl:text>

        <xsl:if test="not(parent::structure)">
            <xsl:text>&#xA;</xsl:text>
        </xsl:if>
    </xsl:template>

    <xsl:template match="field" mode="definition">
        <xsl:param name="indent"/>
        <xsl:value-of select="$indent"/>

        <xsl:value-of select="type"/>
        <xsl:text> </xsl:text>
        <xsl:value-of select="name"/>
        <xsl:for-each select="size">
            <xsl:text>[</xsl:text>
            <xsl:value-of select="."/>
            <xsl:text>]</xsl:text>
        </xsl:for-each>
        <xsl:text>;&#xA;</xsl:text>
    </xsl:template>

	<xsl:template match="enum" mode="definition">
        <xsl:param name="indent"/>
        <xsl:value-of select="$indent"/>

        <xsl:text>enum </xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text> {&#xA;</xsl:text>

        <xsl:apply-templates select="line" mode="definition">
            <xsl:with-param name="indent" select="concat($indent, '    ')"/>
        </xsl:apply-templates>

        <xsl:value-of select="$indent"/>
        <xsl:text>}</xsl:text>
        <xsl:value-of select="@instance"/>
        <xsl:text>;&#xA;</xsl:text>

        <xsl:if test="not(parent::structure)">
            <xsl:text>&#xA;</xsl:text>
        </xsl:if>
    </xsl:template>

    <xsl:template match="enum/line" mode="definition">
        <xsl:param name="indent"/>

        <xsl:value-of select="$indent"/>
        <xsl:value-of select="name"/>

        <xsl:if test="value">
            <xsl:text> = </xsl:text>
        <xsl:value-of select="value"/>
        </xsl:if>
        <xsl:text>,&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="function">
        <!-- Comment -->
        <xsl:text> /**</xsl:text>
        <xsl:for-each select="param">
            <xsl:text>&#xA;  @param </xsl:text>
            <xsl:value-of select="name"/>
        </xsl:for-each>

        <xsl:text>&#xA;  @return </xsl:text>
        <xsl:value-of select="return"/>

        <xsl:text>&#xA;  */&#xA;</xsl:text>

        <!-- Declaration -->
        <xsl:value-of select="$prefix"/>
        <xsl:text> </xsl:text>
        <xsl:value-of select="return"/>
        <xsl:text>&#xA;</xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text>(</xsl:text>

        <xsl:for-each select="param">
            <xsl:text>&#xA;    </xsl:text>
            <xsl:value-of select="type"/>
            <xsl:text> </xsl:text>
            <xsl:value-of select="name"/>
            <xsl:for-each select="size">
                <xsl:text>[</xsl:text>
                <xsl:value-of select="."/>
                <xsl:text>]</xsl:text>
            </xsl:for-each>
            <xsl:if test="position() != last()">

                <xsl:text>,</xsl:text>

            </xsl:if>
        </xsl:for-each>

        <xsl:text>);&#xA;&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="registry/externs/extern">
        <xsl:value-of select="$prefix"/>
        <xsl:text> extern </xsl:text>
        <xsl:value-of select="type"/>
        <xsl:text> _</xsl:text>
        <xsl:value-of select="name"/>
        <xsl:text>_</xsl:text>
        <xsl:for-each select="size">
            <xsl:text>[</xsl:text>
            <xsl:value-of select="."/>
            <xsl:text>]</xsl:text>
        </xsl:for-each>
        <xsl:text>;&#xA;</xsl:text>
    </xsl:template>

</xsl:stylesheet>
