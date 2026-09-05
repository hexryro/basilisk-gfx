<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:include href="helpers.xsl"/>

    <xsl:output method="text"/>

    <xsl:variable name="functionPrefix" select="registry/functionPrefix"/>
    <xsl:variable name="functionPrefixCaps" select="registry/functionPrefixCaps"/>

    <xsl:template match="define|ifdef|ifndef|elifdef">
        <xsl:text>#</xsl:text>
        <xsl:value-of select="name()"/>
        <xsl:text> </xsl:text>
        <xsl:value-of select="@cond"/>
        <xsl:text>&#xA;</xsl:text>
        <xsl:apply-templates select="*"/>
    </xsl:template>

    <xsl:template match="else">
        <xsl:text>#</xsl:text>
        <xsl:value-of select="name()"/>
        <xsl:text>&#xA;</xsl:text>
        <xsl:apply-templates select="*"/>
    </xsl:template>

    <xsl:template match="endif">
        <xsl:text>#endif&#xA;&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="/">
        <xsl:call-template name="add-license"/>

        <xsl:text>#ifndef </xsl:text>
        <xsl:value-of select="$functionPrefixCaps"/>
        <xsl:text>INTERNAL_GEN_H&#xA;</xsl:text>
        <xsl:text>#define </xsl:text>
        <xsl:value-of select="$functionPrefixCaps"/>
        <xsl:text>INTERNAL_GEN_H&#xA;&#xA;</xsl:text>

		<xsl:apply-templates select="registry/includes/internalHeader/include"/>
		<xsl:text>&#xA;</xsl:text>

		<xsl:apply-templates select="registry/functions/function" mode="typedef"/>
        <xsl:text>&#xA;typedef struct {&#xA;</xsl:text>
        <xsl:apply-templates select="registry/functions/function" mode="table"/>
        <xsl:text>} </xsl:text>
        <xsl:value-of select="$functionPrefix"/>
        <xsl:text>FunctionTable;&#xA;&#xA;</xsl:text>

		<xsl:apply-templates select="registry/functions/function" mode="declaration"/>
		<xsl:text>&#xA;</xsl:text>

		<xsl:call-template name="addFunctionTableGetter">
            <xsl:with-param name="prefix" select="'_'"/>
        </xsl:call-template>

		<xsl:text>#endif&#xA;</xsl:text>
    </xsl:template>

	<xsl:template match="registry/includes/internalHeader/include">
        <xsl:text>#include &lt;</xsl:text>
        <xsl:value-of select="."/>
        <xsl:text>&gt;&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="function" mode="table">
		<xsl:if test="not(body) or @type = 'allowBody'">
			<xsl:text>    PFN_</xsl:text>
            <xsl:value-of select="@name"/>
            <xsl:text> </xsl:text>
            <xsl:value-of select="@name"/>
            <xsl:text>;&#xA;</xsl:text>
		</xsl:if>
	</xsl:template>

    <xsl:template match="function" mode="typedef">
		<xsl:if test="not(body) or @type = 'allowBody'">
			<xsl:text>typedef </xsl:text>
            <xsl:value-of select="return"/>
            <xsl:text>(* PFN_</xsl:text>
            <xsl:value-of select="@name"/>
            <xsl:text>)(</xsl:text>

            <xsl:for-each select="param">

                <xsl:if test="type">
                    <xsl:value-of select="type"/>
                    <xsl:text> </xsl:text>
                </xsl:if>

                <xsl:value-of select="name"/>

			    <xsl:for-each select="size">
				    <xsl:text>[</xsl:text>
				    <xsl:value-of select="."/>
				    <xsl:text>]</xsl:text>
			    </xsl:for-each>

                <xsl:if test="position() != last()">
                    <xsl:text>, </xsl:text>
                </xsl:if>

            </xsl:for-each>

            <xsl:text>);&#xA;</xsl:text>
		</xsl:if>
	</xsl:template>

	<xsl:template match="function" mode="declaration">
		<xsl:if test="not(body) or @type = 'allowBody'">
			<xsl:value-of select="/registry/prefix"/>
		    <xsl:text> </xsl:text>
		    <xsl:value-of select="return"/>
		    <xsl:text> _</xsl:text>
		    <xsl:value-of select="@name"/>
		    <xsl:text>(</xsl:text>

		    <xsl:for-each select="param">
			    <xsl:value-of select="type"/>
			    <xsl:text> </xsl:text>
			    <xsl:value-of select="name"/>
			    <xsl:for-each select="size">
				    <xsl:text>[</xsl:text>
				    <xsl:value-of select="."/>
				    <xsl:text>]</xsl:text>
			    </xsl:for-each>
			    <xsl:if test="position() != last()">

				    <xsl:text>, </xsl:text>

			    </xsl:if>
		    </xsl:for-each>

		    <xsl:text>);&#xA;</xsl:text>
		</xsl:if>
	</xsl:template>
</xsl:stylesheet>
