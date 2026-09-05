<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:include href="helpers.xsl"/>

	<xsl:template match="@*|node()">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
    </xsl:template>
	
    <xsl:template match="validationTemplate">
        <function name="{/registry/functionPrefix}enableValidation">
			<return>void</return>
			<body>
                <xsl:text>    </xsl:text>
                <xsl:value-of select="/registry/functionPrefix"/>
                <xsl:text>FunctionTable* definitions = _</xsl:text>
                <xsl:value-of select="/registry/functionPrefix"/>
                <xsl:text>getFunctions();&#xA;</xsl:text>

				<xsl:text>    </xsl:text>
				<xsl:value-of select="/registry/functionPrefix"/>
                <xsl:text>FunctionTable* preval_definitions = _preval_</xsl:text>
			    <xsl:value-of select="/registry/functionPrefix"/>
				<xsl:text>getFunctions();&#xA;</xsl:text>

				<xsl:text>    </xsl:text>
				<xsl:value-of select="/registry/functionPrefix"/>
				<xsl:text>FunctionTable* val_definitions = _val_</xsl:text>
				<xsl:value-of select="/registry/functionPrefix"/>
				<xsl:text>getFunctions();&#xA;</xsl:text>

				<xsl:text>    </xsl:text>
				<xsl:text>val_definitions = _preval_</xsl:text>
				<xsl:value-of select="/registry/functionPrefix"/>
				<xsl:text>setFunctions(val_definitions, definitions);&#xA;</xsl:text>
				
				<xsl:text>    </xsl:text>
				<xsl:text>preval_definitions = _</xsl:text>
				<xsl:value-of select="/registry/functionPrefix"/>
				<xsl:text>setFunctions(preval_definitions, val_definitions);</xsl:text>
			</body>
        </function>
		
        <function name="{/registry/functionPrefix}disableValidation">
	        <return>void</return>
	        <body>
                <xsl:text>    </xsl:text>
                <xsl:value-of select="/registry/functionPrefix"/>
                <xsl:text>FunctionTable* definitions = _</xsl:text>
				<xsl:value-of select="/registry/functionPrefix"/>
				<xsl:text>getFunctions();&#xA;</xsl:text>

				<xsl:text>    _</xsl:text>
				<xsl:value-of select="/registry/functionPrefix"/><xsl:text>setFunctions(definitions, NULL);</xsl:text>
			</body>
        </function>
    </xsl:template>

	<xsl:template match="batchFunctionTemplate">
        <function name="bs_batch{@name}">
            <return>void</return>
            <param><type>bs_Batch*</type><name>batch</name></param>
            <param><type>bs_U32*</type><name>offset</name></param>
            <xsl:copy-of select="param"/>
        </function>
        <function name="bs_push{@name}">
            <return>bs_Range</return>
            <param><type>bs_Batch*</type><name>batch</name></param>
            <xsl:copy-of select="param"/>
        </function>
    </xsl:template>

	<xsl:template match="registry/enums">
        <enums>
            <xsl:apply-templates select="@*|node()"/>
            <xsl:apply-templates select="serializableEnum" mode="enum"/>
        </enums>
    </xsl:template>

    <xsl:template match="registry/functions">
        <functions>
            <xsl:apply-templates select="@*|node()"/>
            <xsl:apply-templates select="/registry/enums/serializableEnum" mode="function"/>
        </functions>
    </xsl:template>

    <xsl:template match="serializableEnum" mode="enum">
        <enum name="bs_{@name}">
            <xsl:copy-of select="line"/>
			<xsl:if test="@count and not(@count = '')">
				<line><name><xsl:value-of select="@count"/></name><value><xsl:value-of select="count(line)"/></value></line>
			</xsl:if>
        </enum>
					
		<xsl:if test="@index = 'true'">
			<enum name="bs_{@name}Index">
				<xsl:for-each select="line">
					<line><name><xsl:value-of select="name"/>_INDEX</name><value><xsl:value-of select="position() - 1"/></value></line>
				</xsl:for-each>
			</enum>
		</xsl:if>
    </xsl:template>

    <xsl:template match="serializableEnum" mode="function">
        <function name="bs_serialize{@name}">
            <return>const char*</return>
            <param><type>bs_<xsl:value-of select="@name"/></type><name>e</name></param>
            <body>
                <xsl:choose>
                    <xsl:when test="@count = 'true'">
                        <xsl:text>    static const char*</xsl:text>
                        <xsl:text> values[</xsl:text>
                        <xsl:value-of select="@count"/>
                        <xsl:text>] = {&#xA;</xsl:text>
                        <xsl:for-each select="line">
                            <xsl:if test="not(name = ../@count) and not(value = preceding-sibling::line/value)">
                                <xsl:text>        [</xsl:text>
                                <xsl:value-of select="name"/>
                                <xsl:text>] = </xsl:text>
                                <xsl:text>"</xsl:text>
                                <xsl:value-of select="name"/>
                                <xsl:text>",&#xA;</xsl:text>
                            </xsl:if>
                        </xsl:for-each>
                        <xsl:text>    };&#xA;&#xA;</xsl:text>
                        <xsl:text>    return values[e];</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>    switch (e) {&#xA;</xsl:text>
                        <xsl:for-each select="line">
							<xsl:if test="not(value = preceding-sibling::line/value)">
								<xsl:text>        case </xsl:text>
								<xsl:value-of select="name"/>
								<xsl:text>: return "</xsl:text>
								<xsl:value-of select="name"/>
								<xsl:text>";&#xA;</xsl:text>
							</xsl:if>
                        </xsl:for-each>
                        <xsl:text>    }&#xA;&#xA;    return NULL;</xsl:text>
                    </xsl:otherwise>
                </xsl:choose>

            </body>
        </function>
		
        <xsl:if test="@deserialize = 'true'">
            <function name="{/registry/functionPrefix}deserialize{@name}">
                <return><xsl:value-of select="/registry/functionPrefix"/><xsl:value-of select="@name"/></return>
                <param><type>const char*</type><name>value</name></param>
                <body>
                    <xsl:text>    </xsl:text>
                    <xsl:for-each select="line">
                        <xsl:text>if (strcmp(value, "</xsl:text>
                        <xsl:value-of select="name"/>
                        <xsl:text>") == 0) return </xsl:text>
                        <xsl:value-of select="name"/>
                        <xsl:text>;&#xA;</xsl:text>
                        <xsl:if test="not(position() = last())">
                            <xsl:text>    else </xsl:text>
                        </xsl:if>
                    </xsl:for-each>
                    <xsl:text>&#xA;    bs_warnF("Failed to deserialize enum value \"%s\"\n", value);&#xA;</xsl:text>
                    <xsl:text>    return 0;</xsl:text>
                </body>
            </function>
        </xsl:if>

		<xsl:if test="@index = 'true'">
			<function name="{/registry/functionPrefix}index{@name}">
				<return>
					<xsl:value-of select="/registry/functionPrefix"/>
					<xsl:value-of select="@name"/>
				</return>
				<param>
					<type>int</type>
					<name>index</name>
				</param>
				<body>
					<xsl:text>    static </xsl:text>
					<xsl:value-of select="/registry/functionPrefix"/>
					<xsl:value-of select="@name"/>
					<xsl:text> table[] = {</xsl:text>
					
					<xsl:for-each select="line">
						<xsl:text>&#xA;        </xsl:text>
						<xsl:value-of select="name"/>
						<xsl:text>,</xsl:text>
					</xsl:for-each>
					<xsl:text>&#xA;    };&#xA;&#xA;    return table[index];</xsl:text>
				</body>
			</function>
		</xsl:if>
    </xsl:template>
    
    <xsl:template match="matrixTemplate">
        <xsl:choose>
            <xsl:when test="rows = columns">
                <xsl:variable name="name" select="rows"/>
				<function type="cglm" name="bs_m{$name}Mul">
                    <return>void</return>
                    <param><type>const bs_mat<xsl:value-of select="$name"/>*</type><name>a</name></param>
                    <param><type>const bs_mat<xsl:value-of select="$name"/>*</type><name>b</name></param>
                    <param><type>const bs_mat<xsl:value-of select="$name"/>*</type><name>result</name></param>
                    <body>    glm_mat<xsl:value-of select="$name"/>_mul(a->v, b->v, result->v);</body>
                </function>
				<function type="cglm" name="bs_m{$name}Transpose">
                    <return>void</return>
                    <param><type>const bs_mat<xsl:value-of select="$name"/>*</type><name>m</name></param>
                    <param><type>const bs_mat<xsl:value-of select="$name"/>*</type><name>result</name></param>
                    <body>    glm_mat<xsl:value-of select="$name"/>_transpose_to(m->v, result->v);</body>
                </function>
				<function type="cglm" name="bs_m{$name}Inverse">
                    <return>void</return>
                    <param><type>const bs_mat<xsl:value-of select="$name"/>*</type><name>m</name></param>
                    <param><type>const bs_mat<xsl:value-of select="$name"/>*</type><name>result</name></param>
                    <body>    glm_mat<xsl:value-of select="$name"/>_inv(m->v, result->v);</body>
                </function>
            </xsl:when>
            <xsl:otherwise>
                <xsl:variable name="name" select="concat(rows, concat('x', columns))"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

    <xsl:template match="vectorTemplate">
		<function type="cglm" name="bs_v{n}Add" comment="Add two {n}D vectors">
			<return>void</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>a</name></param>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>b</name></param>
			<param><type>bs_vec<xsl:value-of select="n"/>*</type><name>out</name></param>
			<body>    glm_vec<xsl:value-of select="n"/>_add(a->a, b->a, out->a);</body>
		</function>
		<function type="cglm" name="bs_v{n}Sub" comment="Subtract two {n}D vectors">
			<return>void</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>a</name></param>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>b</name></param>
			<param><type>bs_vec<xsl:value-of select="n"/>*</type><name>out</name></param>
			<body>    glm_vec<xsl:value-of select="n"/>_sub(a->a, b->a, out->a);</body>
		</function>
		<function type="cglm" name="bs_v{n}Mul" comment="Multiply two {n}D vectors">
			<return>void</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>a</name></param>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>b</name></param>
			<param><type>bs_vec<xsl:value-of select="n"/>*</type><name>out</name></param>
			<body>    glm_vec<xsl:value-of select="n"/>_mul(a->a, b->a, out->a);</body>
		</function>
		<function type="cglm" name="bs_v{n}Div" comment="Divide two {n}D vectors">
			<return>void</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>a</name></param>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>b</name></param>
			<param><type>bs_vec<xsl:value-of select="n"/>*</type><name>out</name></param>
			<body>    glm_vec<xsl:value-of select="n"/>_div(a->a, b->a, out->a);</body>
		</function>
		<function type="cglm" name="bs_v{n}AddS" comment="Add all components of a {n}D vector with a scalar value">
			<return>void</return>
            <param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>v</name></param>
            <param><type>float</type><name>s</name></param>
			<param><type>bs_vec<xsl:value-of select="n"/>*</type><name>out</name></param>
            <body>    *out = (bs_vec<xsl:value-of select="n"/>) {<xsl:for-each select="components/component">v-><xsl:value-of select="."/> + s<xsl:if test="not(position() = last())">, </xsl:if></xsl:for-each> };</body>
		</function>
		<function type="cglm" name="bs_v{n}SubS" comment="Subtract all components of a {n}D vector by a scalar value">
			<return>void</return>
            <param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>v</name></param>
            <param><type>float</type><name>s</name></param>
			<param><type>bs_vec<xsl:value-of select="n"/>*</type><name>out</name></param>
            <body>    *out = (bs_vec<xsl:value-of select="n"/>) {<xsl:for-each select="components/component">v-><xsl:value-of select="."/> - s<xsl:if test="not(position() = last())">, </xsl:if></xsl:for-each> };</body>
		</function>
		<function type="cglm" name="bs_v{n}MulS" comment="Multiply all components of a {n}D vector with a scalar value">
			<return>void</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>v</name></param>
			<param><type>float</type><name>s</name></param>
			<param><type>bs_vec<xsl:value-of select="n"/>*</type><name>out</name></param>
			<body>    glm_vec<xsl:value-of select="n"/>_scale(v->a, s, out->a);</body>
		</function>
		<function type="cglm" name="bs_v{n}DivS" comment="Divide all components of a {n}D vector by a scalar value">
			<return>void</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>v</name></param>
			<param><type>float</type><name>s</name></param>
			<param><type>bs_vec<xsl:value-of select="n"/>*</type><name>out</name></param>
			<body>    glm_vec<xsl:value-of select="n"/>_scale(v->a, 1.0 / s, out->a);</body>
		</function>
		<function type="cglm" name="bs_v{n}Dot"  comment="Dot product">
			<return>float</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>a</name></param>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>b</name></param>
			<body>    return glm_vec<xsl:value-of select="n"/>_dot(a->a, b->a);</body>
        </function>
		<function type="cglm" name="bs_v{n}Distance" comment="Distance between two {n}D vectors">
			<return>float</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>a</name></param>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>b</name></param>
			<body>    return glm_vec<xsl:value-of select="n"/>_distance(a->a, b->a);</body>
        </function>
		<function type="cglm" name="bs_v{n}Magnitude" comment="Magnitude of a {n}D vector">
			<return>float</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>v</name></param>
			<body>    return glm_vec<xsl:value-of select="n"/>_norm(v->a);</body>
        </function>
		<function type="cglm" name="bs_v{n}MagnitudeSqrd" comment="Squared magnitude of a {n}D vector (avoid square root cost)">
			<return>float</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>v</name></param>
			<body>    return glm_vec<xsl:value-of select="n"/>_norm2(v->a);</body>
		</function>
		<function type="cglm" name="bs_v{n}Normalize" comment="Normalize a {n}D vector">
			<return>void</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>v</name></param>
			<param><type>bs_vec<xsl:value-of select="n"/>*</type><name>out</name></param>
			<body>    glm_vec<xsl:value-of select="n"/>_normalize_to(v->a, out->a);</body>
        </function>
		<function type="cglm" name="bs_v{n}Lerp" comment="Linear interpolation between two {n}D vectors">
			<return>void</return>
			<param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>from</name></param>
            <param><type>const bs_vec<xsl:value-of select="n"/>*</type><name>to</name></param>
            <param comment="Interpolant (amount) clamped between 0 and 1"><type>float</type><name>t</name></param>
			<param><type>bs_vec<xsl:value-of select="n"/>*</type><name>out</name></param>
            <body><xsl:for-each select="components/component">    out-><xsl:value-of select="."/> = bs_lerp(from-><xsl:value-of select="."/>, to-><xsl:value-of select="."/>, t);<xsl:if test="not(position() = last())"><xsl:text>&#xA;</xsl:text></xsl:if></xsl:for-each></body>
        </function>
	</xsl:template>

</xsl:stylesheet>
