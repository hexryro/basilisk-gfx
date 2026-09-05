<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:include href="helpers.xsl"/>

    <xsl:output method="text"/>

    <xsl:variable name="functionPrefix" select="registry/functionPrefix"/>
    <xsl:variable name="functionPrefixCaps" select="registry/functionPrefixCaps"/>

    <xsl:template match="/">
        <xsl:call-template name="add-license"/>

        <xsl:text>#ifndef </xsl:text>
        <xsl:value-of select="$functionPrefixCaps"/>
        <xsl:text>PREVALIDATION_H&#xA;</xsl:text>
        <xsl:text>#define </xsl:text>
        <xsl:value-of select="$functionPrefixCaps"/>
        <xsl:text>PREVALIDATION_H&#xA;&#xA;</xsl:text>

        <xsl:apply-templates select="registry/includes/prevalidationHeader/include"/>
		<xsl:text>&#xA;</xsl:text>

		<xsl:call-template name="addFunctionProcsGetter">
			<xsl:with-param name="prefix" select="'_preval_'"/>
		</xsl:call-template>

		<xsl:text>const </xsl:text>
		<xsl:value-of select="/registry/functionPrefix"/>
		<xsl:text>FunctionTable* _preval_</xsl:text>
		<xsl:value-of select="/registry/functionPrefix"/>
		<xsl:text>setFunctions(const </xsl:text>
		<xsl:value-of select="/registry/functionPrefix"/>
		<xsl:text>FunctionTable* a, </xsl:text>
		<xsl:value-of select="/registry/functionPrefix"/>
		<xsl:text>FunctionTable* b);&#xA;</xsl:text>
		<xsl:text>&#xA;</xsl:text>

		<xsl:text>#endif&#xA;</xsl:text>
    </xsl:template>
	
    <xsl:template match="registry/includes/prevalidationHeader/include">
        <xsl:text>#include &lt;</xsl:text>
        <xsl:value-of select="."/>
        <xsl:text>&gt;&#xA;</xsl:text>
    </xsl:template>
</xsl:stylesheet>
