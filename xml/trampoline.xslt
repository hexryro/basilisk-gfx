<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:include href="helpers.xsl"/>

    <xsl:output method="text"/>
    
    <xsl:strip-space elements="*"/>

    <xsl:variable name="prefix" select="registry/prefix"/>
    <xsl:variable name="functionPrefix" select="registry/functionPrefix"/>
    <xsl:variable name="file" select="registry/file"/>

    <xsl:template match="/">
        <xsl:call-template name="add-license"/>
        <xsl:apply-templates select="registry/includes/trampoline/include"/>
        <xsl:text>&#xA;</xsl:text>

		<xsl:call-template name="addFunctionTableSetter">
			<xsl:with-param name="prefix" select="'_'"/>
		</xsl:call-template>

		<xsl:apply-templates select="registry/functions/*" mode="definition"/>
    </xsl:template>

    <xsl:template match="registry/includes/trampoline/include">
        <xsl:text>#include &lt;</xsl:text>
        <xsl:value-of select="."/>
        <xsl:text>&gt;&#xA;</xsl:text>
    </xsl:template>

    <xsl:template match="function" mode="definition">
		<xsl:call-template name="createFunctionBody"/>
    </xsl:template>

</xsl:stylesheet>
